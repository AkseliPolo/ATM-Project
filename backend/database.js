const mysql = require('mysql2');


const db = mysql.createPool({
  host: '127.0.0.1',
  user: 'peppiuser',
  password: 'peppipass',
  database: 'bank_db',      
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
});

module.exports = db;