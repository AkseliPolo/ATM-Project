# Group 15 ATM
 

## Introduction
 
This project was developed as part of the Software Project course. The goal of the project was to design and implement an ATM system, including a database, backend REST API, and an application. The system simulates real ATM functionality such as user authentication with card and PIN, balance checking, cash withdrawal, and viewing transaction history.
 

## Goals
 
The goals we set for our project were to create a working banking database, implement a REST API using Node.js and Express, develop a Qt-based desktop ATM application, and utilize version control with GitHub.
 

## Application Architecture
 
Qt was used for the user interface and for sending HTTP requests to the backend.<br>The REST API handles business logic, communication with the database, authentication, and validation.<br>The MySQL database stores customers, accounts, cards, and transactions.
 
**Data flow:**<br>Qt App → HTTP → REST API → SQL → Database
 

## Database
 
The database includes the following main entities:
 

*   Customer
     
*   Account
     
*   Card
     
*   Transaction
     

The relationships between these entities are:
 

*   One customer can have multiple accounts
     
*   One account belongs to one customer
     
*   One card is linked to one account
     
*   Transactions are linked to accounts
     

## API Endpoints
 
...
 

## Implemented Features
 

*   Debit card functionality
     
*   PIN authentication
     
*   Balance display
     
*   Cash withdrawal
     
*   Transaction history
     
*   PIN timeout
     
*   Full CRUD operations
     
*   Card lock stored in the database
     
*   30-second inactivity timeout
     
*   Transaction browsing
     

## Source Code
 
...