const express = require('express');
const bodyParser = require('body-parser');
const db = require('./database'); // huolehdi että polku on oikein

const app = express();
app.use(bodyParser.json());

// ========================== customers ========================== //

app.post('/customers', async (request, response) => {
  const { fname, lname } = request.body;
  try {
    const [result] = await db.execute(
      'INSERT INTO customers (fname, lname) VALUES (?, ?)',
      [fname, lname]
    );
    response.json({ id: result.insertId, fname, lname });
  } catch (err) {
    response.status(500).json({ error: err.message });
  }
});

app.get('/customers', async (request, response) => {
  try {
    const [rows] = await db.execute('SELECT * FROM customers');
    response.json(rows);
  } catch (err) {
    response.status(500).json({ error: err.message });
  }
});

app.get('/customers/:id', async (req, res) => {
  try {
    const [rows] = await db.execute(
      'SELECT * FROM customers WHERE idCustomers = ?',
      [req.params.id]
    );
    res.json(rows[0]);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});


const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
