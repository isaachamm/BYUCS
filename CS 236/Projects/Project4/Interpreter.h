//
// Created by Isaac Hamm on 7/12/22.
//

#ifndef LAB3_INTERPRETER_H
#define LAB3_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <iostream>

class Interpreter {

private:
    DatalogProgram datalog;
    Database database;

public:
    Interpreter() { }
    Interpreter(DatalogProgram datalog) : datalog(datalog) {}
    Interpreter(DatalogProgram datalog, Database database) : datalog(datalog), database(database) { }

    void run() {
        //call evalSchemes
        evalSchemes();
        //call evalFacts
        evalFacts();
        //evalRules (Proj 4)
        evalRules();
        //call evalQueries
        evalQueries();
        //Note: output is occurring inside of these^ functions

    }

    void evalSchemes() {
        for(Predicate scheme : datalog.getSchemes()) {
            string schemeName;
            Header schemeHeader;
            schemeName = scheme.getName();
            for (Parameter p: scheme.getParameters()) {
                schemeHeader.push_back(p.getValue());
            }
            Relation *newRelation = new Relation;
            newRelation->setName(schemeName);
            newRelation->setHeader(schemeHeader);
            database.addRelation(newRelation);
        }
    }

    void evalFacts() {
        for(Predicate fact : datalog.getFacts()) {
            string factName;
            Tuple factValues;
            factName = fact.getName();
            for(Parameter p : fact.getParameters()) {
                factValues.push_back(p.getValue());
            }
            database.addTuples(factValues, factName);
        }

    }

    void evalRules() {
        unsigned int databaseSizeBefore; // just to let this run once – maybe a do while loop would be better?
        unsigned int databaseSizeAfter;
        unsigned int tuplesAdded = 1;
        unsigned int iterationCounter = 0;
        cout << "Rule Evaluation" << endl;
        while (tuplesAdded != 0) { //or do while
            iterationCounter++;
            tuplesAdded = 0;
            for (Rule rule: datalog.getRules()) {

                cout << rule.getHead().toString() << " :- ";


                //turn body preds into relations
                vector<Predicate> bodyPreds = rule.getBody();
                vector<Relation *> predToRelations;
                string sep;
                for (Predicate p: bodyPreds) {
                    predToRelations.push_back(evaluatePredicate(p));
                    cout << sep << p.toString();
                    sep = ",";
                }
                cout << "." << endl;


                //natural join relations
                Relation *output;
                unsigned int counter = 0;
                for (Relation *r: predToRelations) {
                    if (counter == 0) {
                        output = r;
                        counter++;
                    } else {
                        output = output->naturalJoin(r);
                    }
                }

                //project only columns from rule head
                vector<unsigned int> columnsToKeep;
                for (unsigned int i = 0; i < (rule.getHead().getParameters().size()); ++i) {
                    for (unsigned int j = 0; j < output->getHeader().getAttributes().size(); ++j) {
                        string ruleColumn = rule.getHead().getParameters().at(i).getValue();
                        string outputColumn = output->getHeader().getAttributes().at(j);
                        if (ruleColumn == outputColumn) {
                            columnsToKeep.push_back(j);
                        }
                    }
                }
                output = output->project(columnsToKeep);

                //rename from DB (scheme names!) so we can union
                Relation *preRuleData = database.getRelation(rule.getHead().getName());
                output = output->rename(preRuleData->getHeader().getAttributes());
                output->setName(preRuleData->getName());

                databaseSizeBefore = preRuleData->size();
                //union with the same name (to put into the database)
                output = output->unionFunction(preRuleData);
                database.overwriteRelation(output);

                databaseSizeAfter = output->size();
                tuplesAdded += (databaseSizeAfter - databaseSizeBefore);

            }
        }
        cout << endl;
        cout << "Schemes populated after " << iterationCounter << " passes through the Rules." << endl;
        cout << endl;
    }

    void evalQueries() {
        cout << "Query Evaluation" << endl;
        for(Predicate query: datalog.getQueries()) {
            Relation* result = evaluatePredicate(query);
            //cout for Proj3 -- might have to change for proj 4
            cout << query.toString() << "? ";
            if (result->size() == 0) {
                cout << "No" << endl;
            }
            else {
                cout << "Yes(" << result->size() << ")" << endl;
            }
            cout << result->toString();

        }
    }

    //helper functions

    //This basically just runs a select, project, rename for a given predicate
    Relation* evaluatePredicate(const Predicate& predToEval) {
        Relation* newRelation = new Relation();
        map<string, unsigned int> varTracker;
        unsigned int counter = 0;
        vector<unsigned int> columnsToKeep;

        newRelation = database.getRelation(predToEval.getName());

        //select
        for(Parameter p : predToEval.getParameters()) {
            if(p.isConst()) {
                newRelation = newRelation->select(counter, p.getValue());
            }
            else {
                if (varTracker.find(p.getValue()) != varTracker.end()) { // checking to see if the variable has occurred already
                    newRelation = newRelation->select(varTracker[p.getValue()], counter); //Note: don't need to push these back to columnsToKeep because they're variable duplicates
                }
                else {
                    //add to map
                    varTracker[p.getValue()] = counter;
                    columnsToKeep.push_back(counter); //pushing back the columns that we need to keep (these are the variable columns
                }
            }
            counter++;
        }

        newRelation = newRelation->project(columnsToKeep);

        //rename
        counter = 0;
        set<string> duplicateCheck; //use to check for duplicates in this function
        for(Parameter p : predToEval.getParameters()) {
            if(!p.isConst()) { //check for constants -- those shouldn't be added as names
                string newName = varTracker.find(p.getValue())->first;  //find the name of the variable in the map
                if(duplicateCheck.insert(newName).second) {     //check to make sure we haven't seen it for renaming
                    newRelation = newRelation->rename(counter, newName); //Counter works here because we're going in order through the parameter variables
                    counter++;
                }
            }
        }

        return newRelation;
    }

};


#endif //LAB3_INTERPRETER_H
