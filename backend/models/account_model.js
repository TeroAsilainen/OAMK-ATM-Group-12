const db=require('../database');

const account={
    getAll:function(callback) {
        return db.query('SELECT * FROM account', callback);
    },
    getById:function(id, callback){
        return db.query('SELECT * FROM account WHERE idaccount=?', [id], callback);
    },
    add:function(account_data, callback){
        {
            return db.query('INSERT INTO account VALUES(?,?,?)', [account_data.idaccount, account_data.balance, account_data.credit_limit], callback);
          }
    },
    update:function(id, account_data, callback){
        {
            return db.query('UPDATE account SET balance=?, credit_limit=? WHERE idaccount=?', [ account_data.balance, account_data.credit_limit, id], callback);
        }
    },
    delete:function(id, callback){
        return db.query('DELETE FROM account WHERE idaccount=?', [id], callback);
    },
    debitTransfer:function(procedures_data, callback) {
        return db.query('CALL debit_transfer (?,?,?)', [procedures_data.first_id, procedures_data.second_id, procedures_data.amount], callback);
    },
    debitWithdrawal:function(procedures_data, callback) {
        return db.query('CALL debit_withdrawal (?,?)', [procedures_data.first_id, procedures_data.amount], callback);
    },
    creditTransfer:function(procedures_data, callback) {
        return db.query('CALL credit_transfer (?,?,?)', [procedures_data.first_id, procedures_data.second_id, procedures_data.amount], callback);
    },
    creditWithdrawal:function(procedures_data, callback) {
        return db.query('CALL credit_withdrawal (?,?)', [procedures_data.first_id, procedures_data.amount], callback);
    }
}

module.exports=account;