const db=require('../database');

const customers={
     add(newC, callback){
        return db.query("INSERT INTO customers(fname, lname, address) VALUES(?,?,?)",
        [
            newC.fname,
            newC.lname,
            newC.address
        ], callback);
    },
      getAllCustomers(callback){
        return db.query("SELECT * FROM customers", callback);
    },
    getCustomerWithId(id, callback){
        return db.query("SELECT * FROM customers Where idCustomers = ?",[id], callback);
    },

    updateCustomerWithId(id, newC, callback){
        return db.query("UPDATE customers SET fname = ?, lname = ?, address = ? WHERE idCustomers = ?", [
            newC.fname,
            newC.lname,
            newC.address,
            id
        ], callback);
    },
    deleteCustomerWithId(id, callback){
        return db.query("DELETE FROM customers Where idCustomers = ?",[id], callback);
    }
}

module.exports=customers;