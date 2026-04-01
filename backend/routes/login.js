const express=require('express');
const dotenv=require('dotenv');
const jwt=require('jsonwebtoken');
const router=express.Router();

dotenv.config();

router.post('/', function(request, response){
if(request.body.idAccount && request.body.pin){
    response.json("ok");
}
else{
    console.log("tunnus tai pin puuttuu");
    return response.status(400).json({"message":"tunnus pin eivät täsmää"})
}
});



module.exports=router;