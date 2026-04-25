const express = require('express');
const bodyParser = require('body-parser');
const db = require('./database'); 

const cardRouter=require('./routes/card');
const loginRouter=require('./routes/login');
const customerRouter = require('./routes/customers');
const accountRouter = require('./routes/accounts');
const transactionRouter = require('./routes/transactions');
const jwt=require('jsonwebtoken');
const dotenv=require('dotenv');
const app = express();
app.use(express.json());
dotenv.config();

app.use(bodyParser.json());


app.use('/customers', customerRouter);
app.use('/accounts', accountRouter);
app.use('/transactions', transactionRouter);



app.use('/login', loginRouter);
app.use('/card', cardRouter);

app.use(authenticateToken);

 


function authenticateToken(request, response, next) {
    const authHeader = request.headers['authorization'];

    if (!authHeader) {
      return response.sendStatus(401);
    }

    const token = authHeader.split(' ')[1];

    if (!token) {
      return response.sendStatus(401);
    }

    jwt.verify(token, process.env.MY_SECRET, function(err, user) {
      if (err) {
        return response.sendStatus(403);
      }
      request.user = user;
      next();
    })
  }

module.exports = app;

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
