const express = require('express');
const router = express.Router();
const debit_procedures = require('../models/account_model');

router.post('/', function(request, response){
    debit_procedures.debitTransfer(request.body, function(err, result){
        if(err){
            response.send("-11");
        }
        else {
            response.json(result.affectedRows);

        }
    })
});


router.put('/', function(request, response){
    debit_procedures.debitWithdrawal(request.body, function(err, result){
        if(err){
            response.send("-11");
        }
        else {
            response.json(result.affectedRows);

        }
    })
});

module.exports=router;