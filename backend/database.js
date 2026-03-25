const mysql = require('mysql2');

// Luo yhteyspooli
const db = mysql.createPool({
  host: '127.0.0.1',       // tietokantapalvelin
  user: 'peppiuser',        // oma käyttäjätunnuksesi
  password: 'peppipass',    // oma salasana
  database: 'bank_db',      // tietokanta
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
});

// Käytetään promise-versiota async/await varten
module.exports = db.promise();