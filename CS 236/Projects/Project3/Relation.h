//
// Created by Isaac Hamm on 7/11/22.
//

#ifndef LAB2_RELATION_H
#define LAB2_RELATION_H

#include "Header.h"
#include "Tuple.h"
#include <set>


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

    void addTuple(Tuple t) {
        tuples.insert(t);
    }

    unsigned int size() {
        return tuples.size();
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

};


#endif //LAB2_RELATION_H
