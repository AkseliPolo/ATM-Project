const express = require('express');
const bodyParser = require('body-parser');
const db = require('./database'); 

//const cardRouter=require('./routes/card');
//const loginRouter=require('./routes/login');
const customerRouter = require('./routes/customers');
const accountRouter = require('./routes/accounts');
const transactionRouter = require('./routes/transactions');

const app = express();
app.use(express.json());
app.use(bodyParser.json());


//customers->


app.use('/customers', customerRouter);
app.use('/accounts', accountRouter);
app.use('/transactions', transactionRouter);
// app.post('/customers', async (request, response) => {
//   const { fname, lname } = request.body;
//   try {
//     const [result] = await db.execute(
//       'INSERT INTO customers (fname, lname) VALUES (?, ?)',
//       [fname, lname]
//     );
//     response.json({ id: result.insertId, fname, lname });
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.get('/customers', async (request, response) => {
//   try {
//     const [rows] = await db.execute('SELECT * FROM customers');
//     response.json(rows);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.get('/customers/:id', async (request, response) => {
//   try {
//     const [rows] = await db.execute(
//       'SELECT * FROM customers WHERE idCustomers = ?',
//       [request.params.id]
//     );
//     response.json(rows[0]);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.patch('/customers/:id', async (request, response) => {
//   const { fname, lname } = request.body;

//   try {
//     const [result] = await db.execute(
//       'UPDATE customers SET fname = ?, lname = ? WHERE idCustomers = ?',
//       [fname ?? null, lname ?? null, request.params.id]
//     );
//     response.json(result);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.delete('/customers/:id', async (request, response) => {
//   try {
//     const [result] = await db.execute(
//       'DELETE FROM customers WHERE idCustomers = ?',
//       [request.params.id]
//     );
//     response.json(result);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

//Accounts->

// app.post('/accounts', async (request, response) => {
//   const { idCustomer, balance, credit_limit } = request.body;

//   try {
//     const [result] = await db.execute(
//       'INSERT INTO account (idCustomer, balance, credit_limit) VALUES (?, ?, ?)',
//       [idCustomer, balance ?? 0, credit_limit ?? 0]
//     );
//     response.json({ id: result.insertId });
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.get('/accounts', async (request, response) => {
//   try {
//     const [rows] = await db.execute('SELECT * FROM account');
//     response.json(rows);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.get('/accounts/:id', async (request, response) => {
//   try {
//     const [rows] = await db.execute(
//       'SELECT * FROM account WHERE idAccount = ?',
//       [request.params.id]
//     );
//     response.json(rows[0]);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.get('/customers/:id/accounts', async (request, response) => {
//   try {
//     const [rows] = await db.execute(
//       'SELECT * FROM account WHERE idCustomer = ?',
//       [request.params.id]
//     );
//     response.json(rows);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.delete('/accounts/:id', async (request, response) => {
//   try {
//     const [result] = await db.execute(
//       'DELETE FROM account WHERE idAccount = ?',
//       [request.params.id]
//     );
//     response.json(result);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

//cards->

// app.post('/card', async (request, response) => {
//   const { idAccount, cardNumber, pin, credit_limit, credit_used, expiry_date, card_type } = request.body;

//   try {
//     const [result] = await db.execute(
//       `INSERT INTO card 
//       (idAccount, cardNumber, pin, credit_limit, credit_used, expiry_date, card_type)
//       VALUES (?, ?, ?, ?, ?, ?, ?)`,
//       [idAccount, cardNumber, pin, credit_limit ?? 0, credit_used ?? 0, expiry_date, card_type]
//     );
//     response.json({ id: result.insertId });
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.get('/card', async (request, response) => {
//   try {
//     const [rows] = await db.execute('SELECT * FROM card');
//     response.json(rows);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.delete('/card/:id', async (request, response) => {
//   try{
//     const [result] = await db.execute('DELETE FROM card WHERE idcard = ?', 
//     [request.params.id]
//   );
//     response.json(result);
//   } catch (err) {
//     response.status(500).json({error: err.message });
//   }
// });

// //Transactions->

// app.post('/transactions', async (request, response) => {
//   const { idAccount, amount, type } = request.body;

//   const connection = await db.getConnection();

//   try {
//     await connection.beginTransaction();

//     const [rows] = await connection.execute(
//       'SELECT balance FROM account WHERE idAccount = ?',
//       [idAccount]
//     );

//     const currentBalance = rows[0].balance;

//     let finalAmount;

//     if (type === 'deposit') {
//       finalAmount = amount;
//     } else {
//       if (currentBalance < amount) {
//         await connection.rollback();
//         return response.status(400).json({ error: 'Insufficient funds' });
//       }
//       finalAmount = -amount;
//     }

//     await connection.execute(
//       'INSERT INTO transaction (idAccount, amount, type, date) VALUES (?, ?, ?, NOW())',
//       [idAccount, finalAmount, type]
//     );

//     await connection.execute(
//       'UPDATE account SET balance = balance + ? WHERE idAccount = ?',
//       [finalAmount, idAccount]
//     );

//     await connection.commit();

//     response.json({ message: 'Transaction completed' });

//   } catch (err) {
//     await connection.rollback();
//     response.status(500).json({ error: err.message });
//   } finally {
//     connection.release();
//   }
// });

// app.get('/transactions', async (request, response) => {
//   try {
//     const [rows] = await db.execute('SELECT * FROM transaction');
//     response.json(rows);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.get('/accounts/:id/transactions', async (request, response) => {
//   try {
//     const [rows] = await db.execute(
//       'SELECT * FROM transaction WHERE idAccount = ?',
//       [request.params.id]
//     );
//     response.json(rows);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });

// app.delete('/transactions/:id', async (request, res) => {
//   try {
//     const [result] = await db.execute(
//       'DELETE FROM transaction WHERE idtransaction = ?',
//       [request.params.id]
//     );
//     response.json(result);
//   } catch (err) {
//     response.status(500).json({ error: err.message });
//   }
// });


//app.use(authenticateToken);
// app.use('/login', loginRouter);
// app.use('/card', cardRouter);
// Middleware function that verifies JWT token and blocks unauthorized requests
// function authenticateToken(request, response, next) {
//     const authHeader = request.headers['authorization'];

//     if (!authHeader) {
//       return response.sendStatus(401);
//     }

//     const token = authHeader.split(' ')[1];

//     if (!token) {
//       return response.sendStatus(401);
//     }

//     jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
//       if (err) {
//         return response.sendStatus(403);
//       }
//       request.user = user;
//       next();
//     })
//   }

module.exports = app;

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
