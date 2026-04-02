const express=require('express');
const dotenv=require('dotenv');
const jwt=require('jsonwebtoken');
const bcrypt=require('bcryptjs');
const router=express.Router();
const card=require('../models/card_model');

dotenv.config();

router.post('/', function(request, response){
if(request.body.cardNumber && request.body.pin){
    
    const cardNumber=request.body.cardNumber;
    const pin=request.body.pin;
    card.check_login(cardNumber, function(err, result){
        if(err){
            return response.status(500).json({"error": "palvelinvirhe"});
        }
        else{
            if(result.length > 0){
                bcrypt.compare(pin, result[0].pin, function(bcError, bcResult){
                    if(bcError){
                        return response.status(500).json({"error": "palvelinvirhe"});
                    }
                    else if(bcResult){
                        const token=generateToken(cardNumber);
                        return response.status(200).json({"success":"OK","token":token});
                    }
                    else{
                         return response.status(400).json({"message":"tunnus ja pin eivät täsmää"})
                    }
                });
            }
            else{
                console.log("Tunnusta ei ole tietokannassa");
                return response.status(401).json({"message":"tunnus ja pin eivät täsmää"});
            }
        }
    });
}
else{
    console.log("tunnus tai pin puuttuu");
    return response.status(400).json({"message":"tunnus ja pin eivät täsmää"})
}
});

function generateToken(cardNumber){
    return jwt.sign({cardNumber}, process.env.MY_SECRET, {'expiresIn' : '1800s'});
};

module.exports=router;