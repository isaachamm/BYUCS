//
// Created by Isaac Hamm on 7/11/22.
//

#ifndef LAB2_RELATION_H
#define LAB2_RELATION_H

#include "Header.h"
#include <set>


class Relation {
private:
    string name;
    Header header;
    set<Tuple> tuples;

public:
    Relation() { }
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

    // B == "value"
    Relation select(unsigned int column, string value) {
        Relation outputRelation;
        outputRelation.setHeader(this->header);
        outputRelation.setName("SELECT(" + this->name + ")");

        for (Tuple currTuple : tuples) {
            if (currTuple.at(column) == value) {
                outputRelation.addTuple(currTuple);
            }
        }
        return outputRelation;
    }

    // B == C
    Relation select(unsigned int column1, unsigned int column2) {
        Relation outputRelation;
        outputRelation.setHeader(this->header);
        outputRelation.setName("SELECT(" + this->name + ")");

        for (Tuple currTuple : tuples) {
            if (currTuple.at(column1) == currTuple.at(column2)) {
                outputRelation.addTuple(currTuple);
            }
        }
        return outputRelation;
    }

    // A <- B
    Relation rename(unsigned int columnToRename, string newName) {
        Relation output;
        output.setName(name);
        Header newHeader = header;

        newHeader.at(columnToRename) = newName;

        output.setHeader(newHeader);

        output.setTuples(tuples);

        return output;

    }

    // [A,B,C] <- [E,F,G]

    // pi_{BCD} R
    Relation project(vector<unsigned int> columnsToKeep) {
        //{3,2}
        //set name to something?
        //create a new header (empty)
            //fill header with reordered data
            //(A,B,C,D,E) -> (D,C)
            //Put that header into output relation

        //foreach tuple t
            //new empty tuple
                //fill t with reordered data
                //(1,2,3,4,5) -> (4,3)
            //put that tuple into output relation
    }

};


#endif //LAB2_RELATION_H
