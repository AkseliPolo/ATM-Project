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
            
           db.query("INSERT INTO card(idAccount, cardNumber, pin, expiry_date, card_type) VALUES(?,?,?,?,?)",[
    stu.idAccount,
    stu.cardNumber,
    hashed,
    stu.expiry_date,
    stu.card_type
])
.then(result => callback(null, result)) 
.catch(err => callback(err)); 
            
        }
        
    });
},
check_login: function(id, callback){
return db.query("SELECT pin FROM card WHERE idAccount=?", [id],
     callback)
}
}

module.exports=card;