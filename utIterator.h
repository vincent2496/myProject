#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
#include "number.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    //Iterator *itStruct = s.createIterator();
	Iterator<Term*> *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *it = s.createIterator();
    it->first();
    it->next();
    Struct *s2 = dynamic_cast<Struct *>(it->currentItem());
    Iterator<Term*> *it2 = s2->createIterator();
    it2->first();
    ASSERT_EQ("X", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_EQ("2", it2->currentItem()->symbol());
    ASSERT_FALSE(it2->isDone());
    it2->next();
    ASSERT_TRUE(it2->isDone());
}


TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    // ListIterator it(&l);
    // Iterator* itList = &it;
	Iterator<Term*> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
    Number one(1);
    // NullIterator nullIterator(&one);
    NullIterator<Term*> nullIterator(&one);
    nullIterator.first();
    ASSERT_TRUE(nullIterator.isDone());
    // Iterator * it = one.createIterator();
    Iterator<Term*> * it = one.createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
}


TEST(iterator, BFSStruct){
    Number n1(1);
    Number n2(2);
    Number n3(3);
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Struct s(Atom("s"),{&n1,&n2,&n3,&X,&Y,&Z});
    Iterator<Term*>* it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());    
    it->next(); 
    ASSERT_EQ("Z", it->currentItem()->symbol());    
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, BFSStructList){
    Number one(1);
    Number two(2);
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");   
    List l({ &Z, &two });    
    Struct t(Atom("t"), { &X, &one, &l });
    Struct s(Atom("s"), { &Y, &t, &one });
    Iterator<Term*> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 1, [Z, 2])", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());    
    it->next(); 
    ASSERT_EQ("[Z, 2]", it->currentItem()->symbol());    
    it->next();    
    ASSERT_EQ("Z", it->currentItem()->symbol());    
    it->next();    
    ASSERT_EQ("2", it->currentItem()->symbol());    
    it->next();        
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, DFSStructList){
    Number one(1);
    Number two(2);
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");   
    List l({ &Z, &two });    
    Struct t(Atom("t"), { &X, &one, &l });
    Struct s(Atom("s"), { &Y, &t, &one });
    Iterator<Term*>* it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 1, [Z, 2])", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[Z, 2]", it->currentItem()->symbol());    
    it->next(); 
    ASSERT_EQ("Z", it->currentItem()->symbol());    
    it->next();       
    ASSERT_EQ("2", it->currentItem()->symbol());    
    it->next();        
    ASSERT_EQ("1", it->currentItem()->symbol());    
    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST(iterator, ListBFSIterator){
    Number one(1);
	Number two(2);
    Variable X("X");
    Variable Y("Y");
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"),{ &one, &t, &Y });
    Iterator<Term*>* itList = s.createBFSIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_EQ("X", itList->currentItem()->symbol());
    itList->next();
    ASSERT_EQ("2", itList->currentItem()->symbol());    
    itList->next();    
    ASSERT_TRUE(itList->isDone());
}
TEST(iterator, ListDFSIterator){
    Number one(1);
	Number two(2);
    Variable X("X");
    Variable Y("Y");
    List l1({ &X, &two });
    List l2({ &one, &l1, &Y });
    Iterator<Term*>* itList = l2.createDFSIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("[X, 2]", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("X", itList->currentItem()->symbol());
    itList->next();
    ASSERT_EQ("2", itList->currentItem()->symbol());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());    
    itList->next();    
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, DFSTwoList){
    Number one(1);
    Number two(2); 
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    List l({ &Z, &one });    
    Struct t(Atom("t"), { &X, &two, &l });
    List s({ &Y, &t, &two });
    Iterator<Term*>* it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("t(X, 2, [Z, 1])", it->currentItem()->symbol());
    ASSERT_FALSE(it->isDone());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[Z, 1]", it->currentItem()->symbol());    
    it->next(); 
    ASSERT_EQ("Z", it->currentItem()->symbol());    
    it->next();       
    ASSERT_EQ("1", it->currentItem()->symbol());    
    it->next();        
    ASSERT_EQ("2", it->currentItem()->symbol());    
    it->next();      
    ASSERT_TRUE(it->isDone());
}

#endif
