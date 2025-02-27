var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

var indexRouter = require('./routes/index');
var cardRouter = require('./routes/card');
var userRouter = require('./routes/user');
var cardAccountRouter = require('./routes/card_account');
var accountRouter = require('./routes/account');
var transactionRouter = require('./routes/transaction');
var accountUserRouter = require('./routes/account_user');
var loginRouter = require('./routes/login');
var debit_proceduresRouter = require('./routes/debit_procedures');
var credit_proceduresRouter = require('./routes/credit_procedures');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/login', loginRouter);

app.use(authenticateToken);

app.use('/card', cardRouter);
app.use('/user', userRouter);
app.use('/card_account', cardAccountRouter);
app.use('/account', accountRouter);
app.use('/transaction', transactionRouter);
app.use('/account_user', accountUserRouter);
app.use('/debit_procedures', debit_proceduresRouter);
app.use('/credit_procedures', credit_proceduresRouter);


function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
  
      if (err) return res.sendStatus(403)

      req.user = user
  
      next()
    })
  }

module.exports = app;
