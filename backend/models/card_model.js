const db=require('../database');
const bcrypt=require('bcryptjs');
const saltrounds=12;

const card={
add: function(stu, callback){
    if(!stu.pin){
        return callback("Pin puuttuu!");
    }
    bcrypt.hash(stu.pin,saltrounds,function(err, hashed){
        if(err){
            return callback(err.message);
        }
        else{
            
            return db.query("INSERT INTO card(idAccount, cardNumber, pin, expiry_date, card_type) VALUES(?,?,?,?,?)",[
                stu.idAccount,
                stu.cardNumber,
                hashed,
                stu.expiry_date,
                stu.card_type
            ],callback);
            
        }
        
    });
}
}

module.exports=card;