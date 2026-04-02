const express=require('express');
const customers=require('../models/customers_model');

const router=express.Router();



router.post('/', function(request, response){
    customers.add(request.body, function(err, result){
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
    customers.getAllCustomers(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.get('/:id',function(request, response){
    customers.getCustomerWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.put('/:id',function(request, response){
    customers.updateCustomerWithId(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.delete('/:id',function(request, response){
    customers.deleteCustomerWithId(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

module.exports=router;