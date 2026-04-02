const db=require('../database');
const bcrypt=require('bcryptjs');
const saltrounds=12;

const card={
    // add(newA, callback){
    //     return db.query("INSERT INTO card(idAccount, cardNumber, pin, expiry_date, card_type) VALUES(?,?,?,?,?)",
    //     [
    //         newA.idAccount,
    //         newA.cardNumber,
    //         newA.pin,
    //         newA.expiry_date,
    //         newA.card_type
    //     ], callback);
    // },

    getAllCards(callback){
        return db.query("SELECT * FROM card", callback);
    },

    deleteCard(id, callback){
        return db.query("DELETE FROM card WHERE idcard = ?",[id], callback);
    },
add: function(stu, callback){
    if(!stu.pin){
        return callback("Pin puuttuu!");
    }
    bcrypt.hash(stu.pin,saltrounds,function(err, hashed){
        if(err){
            return callback(err.message);
        }
        else{
            
           db.query("INSERT INTO card(idAccount, cardNumber, pin, expiry_date, card_type) VALUES(?,?,?,?,?)",[
    stu.idAccount,
    stu.cardNumber,
    hashed,
    stu.expiry_date,
    stu.card_type
],
(err, result) => {
        if (err) return callback(err);
        callback(null, result);
    })
// .then(result => callback(null, result)) 
// .catch(err => callback(err)); 
             
        }
        
    });
},
check_login: function(cn, callback){
return db.query("SELECT pin FROM card WHERE cardNumber=?", [cn],
     callback)
}
}

module.exports=card;