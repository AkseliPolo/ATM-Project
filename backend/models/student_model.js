/*const db=require('../database');
const bcrypt=require('bcryptjs');
const saltrounds=12;

const student={
add: function(stu, callback){
    bcrypt.hash(stu.password,saltrounds,function(err, hashed){
        if(err){
            return callback(err.message);
        }
        else{
            return db.query("INSERT INTO customers(fname, lname) VALUES(?,?)",[
                stu.fname,
                stu.lname
            ],callback);
        }
    });
}
}

module.exports=student;*/