const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');


router.get('/:idcard', function(request, response){
  card.getWrongAttemptsById(request.params.idcard, function(err, result){
      if(err){
        response.send("-11");
      }
      else {
        if (result.length > 0) {
          console.log(result[0]);
          response.json(result[0]["wrong_attempts"]);
        }
        else {
          console.log("user does not exists");
          response.send(false);
        }
        
      }
  })
});


router.put('/:idcard', function(request, response){
  card.updateWrongAttempts(request.params.idcard, request.body, function(err, result){
      if(err){
          response.json(err);
      }
      else {
          response.json(result.affectedRows);
      }
  })
});


router.post('/', 
    function(request, response) {
      if(request.body.idcard && request.body.pin){
        const user = request.body.idcard;
        const pass = request.body.pin;
        
          card.checkPin(user, function(dbError, dbResult) {
            if(dbError){
              response.send("-11");
            }
            else{
              if (dbResult.length > 0) {
                bcrypt.compare(pass,dbResult[0].pin, function(err,compareResult) {
                  if(compareResult) {
                    console.log("success");
                    const token = generateAccessToken({ idcard: user });
                    response.send(token);
                  }
                  else {
                      console.log("wrong pin");
                      response.send(false);
                  }			
                }
                );
              }
              else{
                console.log("user does not exists");
                response.send(false);
              }
            }
            }
          );
        }
      else{
        console.log("idcard or pin missing");
        response.send(false);
      }
    }
  );
  
  function generateAccessToken(idcard) {
    dotenv.config();
    return jwt.sign(idcard, process.env.MY_TOKEN, { expiresIn: '10s' });
  }
  
  module.exports=router;