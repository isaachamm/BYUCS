var express = require('express');
var router = express.Router();
const mongoose = require('mongoose');

const dbURL= 'mongodb+srv://isaachamm:iSaac-0402@cluster0.u78fx.mongodb.net/myFirstDatabase?retryWrites=true&w=majority/comments';
mongoose.connect(dbURL);

const Comments = require('../models/Comments');
const Comment = mongoose.model('Comment');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/comments', function (req, res, next) {
  Comment.find(function (err, comments) {
    if (err) {
      return next(err);
    }
    res.json(comments);
  });
});

router.get('/comments/:comment', function (req, res) {
  res.json(req.comment);
});

router.post('/comments', function (req, res, next) {
  const comment = new Comment(req.body);
  comment.save(function (err, comment) {
    if (err) {
      return next(err);
    }
    res.json(comment);
  });
});

router.put('/comments/:comment/upvote', function (req, res, next) {
  req.comment.upvote(function (err, comment) {
    if (err) {
      return next(err);
    }
    res.json(comment);
  });
});

//this is the post route
router.param('comment', function (req, res, next, id) {
  const query = Comment.findById(id);
  query.exec(function (err, comment) {
    if (err || !comment) {
      return next(new Error(`can't find comment with id ${id}`));
    }
    req.comment = comment;
    return next();
  });
});

module.exports = router;
