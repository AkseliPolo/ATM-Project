const db=require('../database');

const transactions={
     add(newC, callback){
        return db.query("INSERT INTO transaction(idAccount, amount, type, date) VALUES(?,?,?,?)",
        [
            newC.idAccount,
            newC.amount,
            newC.type,
            newC.date
        ], callback);
    },
      getAllTransactions(callback){
        return db.query("SELECT * FROM transaction", callback);
    },
    getTransactionWithId(id, callback){
        return db.query("SELECT * FROM transaction Where idtransaction = ?",[id], callback);
    },

     getTransactionWithAccountId(id, callback){
        return db.query("SELECT * FROM transaction Where idAccount = ?",[id], callback);
    },

    updateTransactionWithId(id, newC, callback){
        return db.query("UPDATE transaction SET idAccount = ?, amount = ?, type = ?, date = ? WHERE idtransaction = ?; ", [
            newC.idAccount,
            newC.amount,
            newC.type,
            newC.date,
            id
        ], callback);

    },
    deleteTransactionWithId(id, callback){
        return db.query("DELETE FROM transaction Where idtransaction = ?",[id], callback);
    }
}


module.exports=transactions;