# Inverted-Search-Using-Hashing
An Inverted Search system implemented in C using Hash Tables and Linked Lists for efficient word indexing, searching, and file-based text retrieval.

## Project Overview

This project implements an **Inverted Search System** using **C Programming**, **Hash Tables**, and **Linked Lists**.

The main purpose of the project is to perform fast word searching across multiple text files using the concept of an **Inverted Index**.

An inverted index stores:
- A word
- The files in which the word appears
- Number of occurrences of the word

This concept is widely used in:
- Search Engines
- File Indexing Systems
- Text Retrieval Applications

---

# Features

## Core Functionalities

- Create Database from Multiple Files
- Display Database in Structured Format
- Search Word Efficiently
- Save Database into File
- Update Existing Database
- File Validation
- Duplicate File Detection

---

# Data Structures Used

## Hash Table
- Hash table size : 27
- Index mapping:
  - A-Z → 0 to 25
  - Special Characters → 26

## Linked Lists
### File Linked List
Stores validated input file names.

### Main Linked List
Stores unique words.

### Sub Linked List
Stores:
- File names
- Word occurrence count

---

# Project Structure

```bash
Inverted-Search-Using-Hashing/
│
├── main.c
├── inverted.h
├── create.c
├── display.c
├── search.c
├── save.c
├── update.c
├── file_validation.c
├── file.txt
├── file1.txt
├── file2.txt
├── README.md
```

---

# Working of the Project

## Step 1
User provides multiple `.txt` files through command line.

## Step 2
Files are validated:
- Checks file existence
- Checks `.txt` extension
- Checks empty files
- Removes duplicate entries

## Step 3
Words are extracted from files.

## Step 4
Hash index is generated using the first character of each word.

## Step 5
Words are stored in:
- Main Nodes
- Sub Nodes

## Step 6
User can:
- Search words
- Display database
- Save database
- Update database

---

# Compilation

```bash
gcc *.c
```

OR

```bash
gcc main.c create.c display.c save.c search.c update.c file_validation.c
```

---

# Execution

```bash
./a.out file.txt file1.txt file2.txt
```

---

# Menu Driven Operations

```txt
1. Create Database
2. Display Database
3. Save Database
4. Search
5. Update Database
6. Exit
```

---

# Sample Input Files

## file.txt

```txt
Inverted index is a powerful data structure
Search engines use inverted index to improve performance
```

## file1.txt

```txt
Hello Everyone , How are you
```

---

# Sample Output

```txt
INDEX      WORD        FILECOUNT   FILENAME     WORDCOUNT

8          inverted    1           file.txt     1
7          Hello       2           file1.txt    1
```

---

# Key Concepts Learned

- Hashing
- Linked Lists
- File Handling
- Dynamic Memory Allocation
- String Manipulation
- Data Structures
- Search Optimization
- Inverted Indexing

---

# Applications

- Search Engines
- Text Search Systems
- File Indexing
- Information Retrieval Systems
- Document Search Applications

---

# Future Enhancements

- Case-insensitive Search
- Stop-word Removal
- Phrase Searching
- Ranking Algorithms
- GUI Integration
- Database Storage
- Web-based Search Engine

---

# Technologies Used

- C Programming Language
- GCC Compiler
- Hash Tables
- Linked Lists
- Dynamic Memory Allocation

---

# Author

## Pavan YDNS

---

# License

This project is developed for educational and learning purposes.
