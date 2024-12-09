#pragma once

#include "hash.h"
#include <vector>
#include <functional>
#include <iostream>

template <class T, size_t SIZE>
class Twox_hash : public Hash<T, SIZE> {
    enum class STATUS : char { OPEN, FILLED };

private:
    std::hash<T> primary_hash;   // Primary hash function
    std::hash<size_t> secondary_hash; // Secondary hash function for resolving collisions

public:
    std::vector<T> data;         // The data storage for the hash table
    std::vector<STATUS> status;  // The status vector to track bucket state

    Twox_hash() {
        // Initialize the table with all OPEN buckets
        data.resize(SIZE);
        status.resize(SIZE, STATUS::OPEN);
    }

    void insert(T new_data) {
        size_t addr = primary_hash(new_data) % SIZE; // Compute primary hash
        size_t original_addr = addr;

        // If the primary bucket is filled, use secondary hashing
        if (status[addr] == STATUS::FILLED) {
            size_t step = secondary_hash(new_data) % (SIZE - 1) + 1; // Secondary hash step
            do {
                addr = (addr + step) % SIZE; // Probe using secondary hash
                if (DEBUG) std::cerr << "(*) Collision, trying address " << addr << "\n";
            } while (status[addr] == STATUS::FILLED && addr != original_addr);
        }

        // If no available bucket is found through secondary hash, use linear probing
        if (status[addr] == STATUS::FILLED) {
            if (DEBUG) std::cerr << "(*) Resorting to linear probing.\n";
            addr = original_addr;
            while (status[addr] == STATUS::FILLED) {
                addr = (addr + 1) % SIZE; // Linear probing
                if (DEBUG) std::cerr << "(*) Probing to address " << addr << "\n";
            }
        }

        // Insert data into the available bucket
        data[addr] = new_data;
        status[addr] = STATUS::FILLED;

        if (DEBUG) std::cerr << "(+) Inserted " << new_data << " at " << addr << "\n";
    }

    bool search(T key) {
        size_t addr = primary_hash(key) % SIZE; // Compute primary hash
        size_t original_addr = addr;

        // Check primary hash bucket
        if (status[addr] == STATUS::FILLED && data[addr] == key) {
            if (DEBUG) std::cerr << "(+) Found " << key << " at primary address " << addr << "\n";
            return true;
        }

        // Use secondary hash to search
        size_t step = secondary_hash(key) % (SIZE - 1) + 1;
        addr = (addr + step) % SIZE;

        while (status[addr] == STATUS::FILLED) {
            if (data[addr] == key) {
                if (DEBUG) std::cerr << "(+) Found " << key << " at address " << addr << "\n";
                return true;
            }
            addr = (addr + step) % SIZE; // Continue probing with secondary hash
            if (addr == original_addr) break; // Stop if looped back to start
        }

        // Resort to linear probing if not found using secondary hash
        addr = original_addr;
        while (status[addr] == STATUS::FILLED) {
            if (data[addr] == key) {
                if (DEBUG) std::cerr << "(+) Found " << key << " at address " << addr << "\n";
                return true;
            }
            addr = (addr + 1) % SIZE; // Linear probing
        }

        if (DEBUG) std::cerr << "(-) Key " << key << " not found.\n";
        return false; // Key not found
    }

    void print() {
        std::cout << "Hash table contents:\n";
        for (size_t i = 0; i < SIZE; ++i) {
            std::cout << i << ": ";
            if (status[i] == STATUS::FILLED) {
                std::cout << data[i];
            } else {
                std::cout << "EMPTY";
            }
            std::cout << "\n";
        }
        std::cout << "---\n";
    }
};