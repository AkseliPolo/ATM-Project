const express = require('express');
const bodyParser = require('body-parser');
const db = require('./database'); 

const cardRouter=require('./routes/card');
const loginRouter=require('./routes/login');
const customerRouter = require('./routes/customers');
const accountRouter = require('./routes/accounts');
const transactionRouter = require('./routes/transactions');

const app = express();
app.use(express.json());
app.use(bodyParser.json());


app.use('/customers', customerRouter);
app.use('/accounts', accountRouter);
app.use('/transactions', transactionRouter);

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




//app.use(authenticateToken);
 app.use('/login', loginRouter);
 app.use('/card', cardRouter);
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
