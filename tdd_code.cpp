//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     RICHARD KOCIAN <xkocia19@stud.fit.vutbr.cz>
// $Date:       $2022-03-10
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author RICHARD KOCIAN
 *
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find/GetHead ...
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "singly linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue() {
    m_pHead = nullptr;

}

PriorityQueue::~PriorityQueue() {
    while (m_pHead != nullptr) {
        Remove(m_pHead->value);
    }
}

void PriorityQueue::Insert(int value) {
    auto newElement = new Element_t;
    if (m_pHead != nullptr) {
        if (m_pHead->value <= value) {
            newElement->pNext = m_pHead;
            newElement->value = value;
            m_pHead = newElement;
        } else {
            auto elementPointer = m_pHead->pNext;
            auto previousElement = m_pHead;
            while (elementPointer != nullptr) {
                if (elementPointer->value <= value) {
                    newElement->pNext = elementPointer;
                    newElement->value = value;
                    previousElement->pNext = newElement;
                    break;
                } else {
                    previousElement = elementPointer;
                    elementPointer = elementPointer->pNext;
                }
            }
            if (elementPointer == nullptr) {
            newElement->pNext = nullptr;
            newElement->value = value;
            previousElement->pNext = newElement;
            }
        }
    } else {
        newElement->pNext = nullptr;
        newElement->value = value;
        //Element_t newElement{nullptr, value};
        m_pHead = newElement;
    }

}

bool PriorityQueue::Remove(int value) {
    if (m_pHead != nullptr) {
        auto pointer = m_pHead;
        if (m_pHead->value == value) {
            m_pHead = pointer->pNext;
            delete pointer;
            return true;
        } else {
            pointer = pointer->pNext;
            auto previousElement = m_pHead;
            while (pointer!= nullptr) {
                if (pointer->value == value) {
                    previousElement->pNext = pointer->pNext;
                    delete pointer;
                    return true;
                } else {
                    previousElement = previousElement->pNext;
                    pointer = pointer->pNext;
                }
            }
        }
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value) {
    auto *elementPointer = m_pHead;
    while (elementPointer != nullptr) {
        if (elementPointer->value == value) {
            return elementPointer;
        } else {
            elementPointer = elementPointer->pNext;
        }
    }
    return NULL;
}

size_t PriorityQueue::Length() {
    auto elementPointer = m_pHead;
    size_t counter = 0;
    while (elementPointer != nullptr) {
        counter++;
        elementPointer = elementPointer->pNext;
    }
    return counter;
}

PriorityQueue::Element_t *PriorityQueue::GetHead() {
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
