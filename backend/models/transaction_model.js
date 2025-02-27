const db=require('../database');

const transaction={
    getAll:function(callback) {
        return db.query('SELECT idtransaction, idaccount, action, amount, date_format(date, "%d.%m.%Y") as date FROM transaction', callback);
    },
    getByIdaccount:function(id, transaction_data, callback){
        return db.query('SELECT idaccount, action, amount, date FROM transaction WHERE idaccount=? ORDER BY date DESC LIMIT ? OFFSET ?',[id, 5, transaction_data.offset],callback);
    },
    add:function(transaction_data, callback){
        return db.query('INSERT INTO transaction(idaccount, date, action, amount) VALUES(?,?,?,?)',[transaction_data.idaccount, transaction_data.date, transaction_data.action, transaction_data.amount], callback);
    },
    update:function(id,transaction_data, callback){
        return db.query('UPDATE transaction SET idaccount=?, date=?, action=?, amount=? WHERE idtransaction=?',[transaction_data.idaccount, transaction_data.date, transaction_data.action, transaction_data.amount, id], callback);
    },
    delete:function(id, callback){
        return db.query('DELETE FROM transaction WHERE idtransaction=?', [id], callback);
    },
}

module.exports=transaction;