const express=require('express');
const transactions=require('../models/transactions_model');
const transactionsModel = require("../models/transactions_model");

const router=express.Router();

router.post('/', function(request, response){
    transactions.add(request.body, function(err, result){
        if(err)
        {
            response.send(err);
        }
        else{
            response.json(result);
            
        }
        
    });
});

router.get('/',function(request, response){
    transactions.getAllTransactions(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.get('/:id',function(request, response){
    transactions.getTransactionWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.get("/account/:id", (req, res) => {
    const accountId = req.params.id;
    const limit = parseInt(req.query.limit) || 10;
    const offset = parseInt(req.query.offset) || 0;

    transactionsModel.getTransactionWithAccountIdPaged(
        accountId,
        limit,
        offset,
        (err, result) => {
            if (err) {
                console.error(err);
                return res.status(500).send(err);
            }

            res.json(result);
        }
    );
});

router.put('/:id',function(request, response){
    transactions.updateTransactionWithId(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.delete('/:id',function(request, response){
    transactions.deleteTransactionWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.post('/cardTransaction', function(request, response){
    transactions.cardTransaction(request.body, function(err, result){
        if(err){
            response.send(err);
        } else {
            response.json(result);
        }
    });
});

module.exports=router;