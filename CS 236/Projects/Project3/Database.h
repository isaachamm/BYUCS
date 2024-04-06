//
// Created by Isaac Hamm on 7/12/22.
//

#ifndef LAB3_DATABASE_H
#define LAB3_DATABASE_H

#include "Relation.h"
#include <map>

class Database {

private:
    map<string, Relation*> database;

public:
    Database() {};
    ~Database() {};

    const map<string, Relation *> &getDatabase() const { return database; }
    void setDatabase(const map<string, Relation *> &database) { Database::database = database; }

    Relation* getRelation(string name) {
        Relation* mapRelation = new Relation();
        mapRelation = database[name];
        return mapRelation;
    }

    void addRelation(Relation* newRelation) {
        database.insert(pair<string, Relation*>(newRelation->getName(), newRelation));
    }

    void addTuples(Tuple toAdd, string relationName) {
        database[relationName]->addTuple(toAdd);
    }

};


#endif //LAB3_DATABASE_H
