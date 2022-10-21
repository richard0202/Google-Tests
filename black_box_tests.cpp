//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     RICHARD KOCIAN <xkocia19@stud.fit.vutbr.cz>
// $Date:       $2022-03-10
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author RICHARD KOCIAN
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

class EmptyTree : public ::testing::Test {
protected:
    BinaryTree *emptyBinaryTree;

    virtual void SetUp() {
        emptyBinaryTree = new BinaryTree();
    }

    virtual void TearDown() {
        delete emptyBinaryTree;
    }
};

class NonEmptyTree : public ::testing::Test {
protected:
    BinaryTree *nonEmptyBinaryTree;

    virtual void SetUp() {
        nonEmptyBinaryTree = new BinaryTree();
        std::vector<int> vector1;
        for (int i = 1; i <= 10; i++) {
            vector1.push_back(i);
        }
        std::vector<std::pair<bool, Node_t *> > vector2;
        nonEmptyBinaryTree->InsertNodes(vector1, vector2);
    }

    virtual void TearDown() {
        delete nonEmptyBinaryTree;
    }
};

class TreeAxioms : public ::testing::Test {
protected:
    BinaryTree *treeAxioms;

    virtual void SetUp() {
        treeAxioms = new BinaryTree();
        std::vector<int> vector1;
        for (int i = 1; i <= 10; i++) {
            vector1.push_back(i);
        }
        std::vector<std::pair<bool, Node_t *> > vector2;
        treeAxioms->InsertNodes(vector1, vector2);

    }

    virtual void TearDown() {
        delete treeAxioms;
    }
};


//====================================EmptyBinaryTree====================================//

TEST_F(EmptyTree, InsertNode) {
    ASSERT_NO_THROW(emptyBinaryTree->InsertNode(2));
    EXPECT_EQ(emptyBinaryTree->GetRoot()->key, 2);
}

TEST_F(EmptyTree, InsertNode_Insert_twice) {
    ASSERT_TRUE(emptyBinaryTree->InsertNode(1).first);
    ASSERT_FALSE(emptyBinaryTree->InsertNode(1).first);
    EXPECT_EQ(emptyBinaryTree->GetRoot()->key, 1);
}

TEST_F(EmptyTree, DeleteNode) {
    EXPECT_NO_THROW(emptyBinaryTree->DeleteNode(2));
}

TEST_F(EmptyTree, DeleteNode_False) {
    EXPECT_FALSE(emptyBinaryTree->DeleteNode(2));
}

TEST_F(EmptyTree, FindNode) {
    EXPECT_NO_THROW(emptyBinaryTree->FindNode(1));
}

TEST_F(EmptyTree, FindNode_NULL) {
    EXPECT_EQ(emptyBinaryTree->FindNode(1), nullptr);
}


//====================================NonEmptyBinaryTree====================================//

TEST_F(NonEmptyTree, InsertNode) {
    EXPECT_NO_THROW(nonEmptyBinaryTree->InsertNode(20));
    EXPECT_TRUE(nonEmptyBinaryTree->InsertNode(21).first);
    EXPECT_FALSE(nonEmptyBinaryTree->InsertNode(1).first);
}

TEST_F(NonEmptyTree, DeleteNode) {
    EXPECT_TRUE(nonEmptyBinaryTree->DeleteNode(1));
    EXPECT_FALSE(nonEmptyBinaryTree->DeleteNode(22));
}

TEST_F(NonEmptyTree, FindNode) {
    EXPECT_NO_THROW(nonEmptyBinaryTree->FindNode(2));
    EXPECT_EQ(nonEmptyBinaryTree->FindNode(2)->key,2);
}

TEST_F(NonEmptyTree, NULL) {
    EXPECT_EQ(nonEmptyBinaryTree->FindNode(-5), nullptr);
}

//====================================Axiomy====================================//

TEST_F(TreeAxioms, Axiom1) {
    std::vector<Node_t *> leafNodes;
    treeAxioms->GetLeafNodes(leafNodes);

    for (int i = 0; i < leafNodes.size(); i++) {
        EXPECT_EQ(leafNodes[i]->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2) {
    std::vector<Node_t *> allNodes;
    treeAxioms->GetAllNodes(allNodes);

    for (int i = 0; i < allNodes.size(); i++) {
        if (allNodes[i]->color == RED) {
            EXPECT_EQ(allNodes[i]->pRight->color, BLACK);
            EXPECT_EQ(allNodes[i]->pLeft->color, BLACK);
        }
    }
}

TEST_F(TreeAxioms, Axiom3) {
    std::vector<int> black_count;
    std::vector<Node_t *> leafNodes;
    treeAxioms->GetLeafNodes(leafNodes);
    for (int i = 0; i < leafNodes.size(); i++) {
        black_count.push_back(0);
        Node_t *parent = leafNodes[i]->pParent;
        while (parent != treeAxioms->GetRoot()) {
            if (parent->color == BLACK) {
                black_count[i]++;
            }
            parent = parent->pParent;
        }
        if (i > 1) {
            EXPECT_EQ(black_count[i-1], black_count[i]);
        }
    }
}


//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
