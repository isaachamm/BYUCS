//
// Created by Isaac Hamm on 7/11/22.
//

#ifndef LAB2_RELATION_H
#define LAB2_RELATION_H

#include "Header.h"
#include "Tuple.h"
#include <set>
#include <map>


class Relation {
private:
    string name;
    Header header;
    set<Tuple> tuples;

public:
    Relation() {}
    ~Relation() {}

    const string &getName() const { return name; }
    const set<Tuple> &getTuples() const { return tuples; }
    const Header &getHeader() const { return header; }
    void setName(const string &name) { Relation::name = name; }
    void setHeader(const Header &header) { Relation::header = header; }
    void setTuples(const set<Tuple> &tuples) { Relation::tuples = tuples; }

    bool addTuple(Tuple t) {
        return tuples.insert(t).second;
    }

    unsigned int size() {
        return tuples.size();
    }

    bool isEmpty() {
        return tuples.empty();
    }

    string toString() {
        stringstream out;
        for(Tuple currTuple : tuples) {
            if(currTuple.size() > 0) {
                out << "  " << currTuple.toString(header) << endl;
            }
        }
        return out.str();
    }

    // B == "value"
    Relation* select(unsigned int column, string value) {
        Relation* outputRelation = new Relation();

        if(column > this->header.size()) {
            throw "SELECT column tried to access out of  bounds";
        }

        outputRelation->setHeader(this->header);
        outputRelation->setName("SELECT(" + this->name + ")");

        for (Tuple currTuple : tuples) {
            if (currTuple.at(column) == value) {
                outputRelation->addTuple(currTuple);
            }
        }
        return outputRelation;
    }

    // B == C
    Relation* select(unsigned int column1, unsigned int column2) {
        Relation* outputRelation = new Relation();

        if(column1 > this->header.size() || column2 > this->header.size()) {
            throw "SELECT tried to access out of bounds";
        }

        outputRelation->setHeader(this->header);
        outputRelation->setName("SELECT(" + this->name + ")");

        for (Tuple currTuple : tuples) {
            if (currTuple.at(column1) == currTuple.at(column2)) {
                outputRelation->addTuple(currTuple);
            }
        }
        return outputRelation;
    }

    // A <- B
    Relation* rename(unsigned int columnToRename, string newName) {
        Relation* output = new Relation();

        Header newHeader = header;
        newHeader.at(columnToRename) = newName;

        output->setName(name);
        output->setHeader(newHeader);
        output->setTuples(tuples);

        return output;

    }

    //overloaded to pass in new names for all columns ( [A,B,C] <- [E,F,G] )
    Relation* rename(vector<string> newAttributes) { //Attributes are column names
        Relation* output = new Relation();

        Header newHeader(newAttributes);
        output->setHeader(newHeader);
        output->setName(name);
        output->setTuples(tuples);

        return output;
    }

    // pi_{BCD} R
    Relation* project(vector<unsigned int> columnsToKeep) {
        //{3,2}
        Relation *output = new Relation();

        //copy old name
        output->setName(name);

        //create a new header (empty)
        Header newHeader;
        //fill header with reordered data i.e., (A,B,C,D,E) -> (D,C)
        for (unsigned int column: columnsToKeep) {
            newHeader.push_back(header.at(column));
        }
        //Put that header into output relation
        output->setHeader(newHeader);

        //foreach tuple t –– we need this because tuples is a set, and we have to add data from each tuple
        for (Tuple t: tuples) {
            //new empty tuple
            Tuple newTuple;
            //fill t with reordered data i.e., (1,2,3,4,5) -> (4,3)
            for (unsigned int column: columnsToKeep) {
                newTuple.push_back(t.at(column));
            }
            //put that tuple into output relation
            output->addTuple(newTuple);
        }

        return output;
    }


    Relation* unionFunction(Relation* toUnion) {
        Relation* r1 = this;
        Relation* r2 = toUnion;

        Relation* output = new Relation();

        //set name for union relation
        output->setName(r2->getName());

        //header has to be the same for both
        output->setHeader(r1->getHeader());

        //add tuples from r2 to r1 (checking for duplicates as we go)
        output->setTuples(r2->getTuples());
//        if (r1->isEmpty()) {
//            for(Tuple t : r1->getTuples()) {
//                cout << "  " << t.toString(r1->header) << endl;
//            }
//        }
//        else {
            for (Tuple t: r1->getTuples()) {
                if (output->addTuple(t)) {
                    cout << "  " << t.toString(output->header) << endl;
                }
            }
//        }

        return output;
    }

    Relation* naturalJoin(Relation* other) {
        // giving clearer names to the 'this' and 'other' relations
        Relation* r1 = this;
        Relation* r2 = other;

        Relation* output = new Relation();

        // set name of output relation
        output->setName(r1->getName() + " |x| " + r2->getName());

        // calculate header overlap of 'this' and 'other' relations
        Header header1 = r1->getHeader();
        Header header2 = r2->getHeader();

        map<unsigned int, unsigned int> overlap; //map to keep track of h1/h2 overlap
        set<unsigned int> uniqueColumns;        //set to keep track of columns in h2 not in h1
        bool found;

        for(unsigned int attribute2 = 0; attribute2 < header2.size(); attribute2++) {
            found = false;
            for(unsigned int attribute1 = 0; attribute1 < header1.size(); attribute1++) {   //nested for loop to compare header attributes
                if(header2.getAttributes().at(attribute2) == header1.getAttributes().at(attribute1)) {
                    found = true;       //make true so doesn't add to unique columns
                    overlap.insert(pair<unsigned int, unsigned int>(attribute1, attribute2));
                }
            }
            if(!found) {
                uniqueColumns.insert(attribute2);
            }
        }

        // combine headers -- will be the header for 'output'
        Header newHeader = combineHeaders(header1, header2, uniqueColumns);
        output->setHeader(newHeader);

        // combine tuples -- will be the tuples for 'output'
        for(Tuple tuple1 : r1->getTuples()) {
            for(Tuple tuple2 : r2->getTuples()) {
                if(isJoinable(tuple1, tuple2, overlap)) {
                    Tuple tupleToAdd = combineTuples(tuple1, tuple2, uniqueColumns);
                    output->addTuple(tupleToAdd);
                }

            }
        }
        return output;
    }

    Header combineHeaders(Header h1, Header h2, set<unsigned int> uniqueColumns) {
        Header newHeader(h1.getAttributes());
        for(auto column : uniqueColumns) {
            newHeader.push_back(h2.at(column));
        }

        return newHeader;
    }

    bool isJoinable(Tuple tuple1, Tuple tuple2, map<unsigned int, unsigned int> overlap) {
        for(auto column : overlap) {
            if(tuple1.at(column.first) != tuple2.at(column.second)) {
                return false;
            }
        }
        return true;
    }

    Tuple combineTuples(Tuple t1, Tuple t2, set<unsigned int> uniqueColumns) {
        Tuple newTuple(t1.getValues());
        for(auto column : uniqueColumns) {
            newTuple.push_back(t2.at(column));
        }

        return newTuple;
    }

};


#endif //LAB2_RELATION_H
