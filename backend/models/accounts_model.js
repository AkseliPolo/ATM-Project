const db=require('../database');

const accounts={
     add(newA, callback){
        return db.query("INSERT INTO account(idCustomer, balance, credit_limit, credit_used) VALUES(?,?,?,?)",
        [
            newA.idCustomer,
            newA.balance,
            newA.credit_limit,
            newA.credit_used
        ], callback);
    },
      getAllAccounts(callback){
        return db.query("SELECT * FROM account", callback);
    },
    getAccountWithId(id, callback){
        return db.query("SELECT * FROM account Where idAccount = ?",[id], callback);
    },
    

      getBalanceWithId(id, callback){
         return db.query("SELECT balance FROM account Where idAccount = ?",[id], callback);
     },

   
    getBalanceWithCardNum(cardNumber, callback) {
    return db.query(
        `SELECT a.balance
         FROM account a
         JOIN card c ON c.idAccount = a.idAccount
         WHERE c.cardNumber = ?`,
        [cardNumber],
        callback
    );
},

    getAccountWithCustomerId(id, callback){
        return db.query("SELECT * FROM account Where idCustomer = ?",[id], callback);
    },

    updateAccountWithId(id, newA, callback){
        return db.query("UPDATE customers SET idCustomer = ?, balance = ?, credit_limit = ?, credit_used = ? WHERE idCustomers = ?", [
            newA.idCustomer,
            newA.balance,
            newA.credit_limit,
            newA.credit_used,
            id
        ], callback);
    },
    deleteAccountWithId(id, callback){
        return db.query("DELETE FROM account Where idAccount = ?",[id], callback);
    }
}

module.exports=accounts;