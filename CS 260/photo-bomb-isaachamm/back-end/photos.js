const mongoose = require('mongoose');
const express = require("express");
const router = express.Router();

// Configure multer so that it will upload to '/public/images'
const multer = require('multer')
const upload = multer({
	//have to change this for DO
  dest: '../front-end/public/images/',
  limits: {
    fileSize: 50000000
  }
});

const users = require("./users.js");
const User = users.model;
const validUser = users.valid;

const photoSchema = new mongoose.Schema({
	user: {
	  type: mongoose.Schema.ObjectId,
	  ref: 'User'
	},
	username: String,
	path: String,
	title: String,
	description: String,
	created: {
	  type: Date,
	  default: Date.now
	},
});

const commentSchema = new mongoose.Schema({
	user: {
		type: mongoose.Schema.ObjectId,
		ref: 'User'
	},
	username: String,
	comment: String,
	photo: {
		type: mongoose.Schema.ObjectId,
		ref: 'Photo'
	},
	created: {
		type: Date,
		default: Date.now
	},
});
  
const Photo = mongoose.model('Photo', photoSchema);
const Comment = mongoose.model('Comment', commentSchema);

// get my photos
router.get("/", validUser, async (req, res) => {
	// return photos
	try {
	  let photos = await Photo.find({
		user: req.user
	  }).sort({
		created: -1
	  }).populate('user');
	  return res.send(photos);
	} catch (error) {
	  console.log(error);
	  return res.sendStatus(500);
	}
});

// get all photos
router.get("/all", async (req, res) => {
	try {
	  let photos = await Photo.find().sort({
		created: -1
	  }).populate('user');
	  return res.send(photos);
	} catch (error) {
	  console.log(error);
	  return res.sendStatus(500);
	}
});

//get comments for a photo
router.get("/comment/:id", async (req, res) => {
	try {
		let photo = await Photo.findOne({
			_id: req.params.id
		});
		let comments = await Comment.find({
			photo: photo
		}).sort({
			created: -1
		}).populate('user', 'photo');
		return res.send(comments);
	} catch (error) {
		console.log(error);
	}
});

//Post a comment for a photo
router.post("/comment/:id", validUser, async (req, res) => {
	try {
		let photo = await Photo.findOne({
			_id: req.params.id
		});
		let newComment = new Comment({
			user: req.user,
			username: req.user.username,
			comment: req.body.comment,
			photo: photo,
		});
			await newComment.save();
			return res.sendStatus(200);
	} catch (error) {
		console.log(error);
	}
});

router.get("/single/:id", async (req, res) => {
	try {
		let photo = await Photo.find({
			_id: req.params.id
		});
		return res.send(photo);
	} catch (error) {
		console.log(error);
		return res.sendStatus(500);
	}
});

// upload photo
router.post("/", validUser, upload.single('photo'), async (req, res) => {
	// check parameters
	if (!req.file)
	  return res.status(400).send({
		message: "Must upload a file."
	});
  
	const photo = new Photo({
	  user: req.user,
	  username: req.user.username,
	  path: "/images/" + req.file.filename,
	  title: req.body.title,
	  description: req.body.description,
	});
	try {
	  await photo.save();
	  return res.sendStatus(200);
	} catch (error) {
	  console.log(error);
	  return res.sendStatus(500);
	}
});

module.exports = {
	model: Photo,
	model: Comment,
	routes: router,
}