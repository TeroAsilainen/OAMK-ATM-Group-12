const express = require('express');
const router = express.Router();
const credit_procedures = require('../models/account_model');

router.post('/', function(request, response){
    credit_procedures.creditTransfer(request.body, function(err, result){
        if(err){
            response.send("-11");
        }
        else {
            response.json(result.affectedRows);

        }
    })
});


router.put('/', function(request, response){
    credit_procedures.creditWithdrawal(request.body, function(err, result){
        if(err){
            response.send("-11");
        }
        else {
            response.json(result.affectedRows);

        }
    })
});

module.exports=router;