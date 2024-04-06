const express = require('express');
const bodyParser = require("body-parser");
const mongoose = require('mongoose');

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: false
}));

//This goes on the listen port 80 page
// location /api {
//   proxy_pass http://localhost:3000;
//   proxy_http_version 1.1;
//   proxy_set_header Upgrade $http_upgrade;
//   proxy_set_header Connection 'upgrade';
//   proxy_set_header Host $host;
//   proxy_cache_bypass $http_upgrade;
// }


// connect to the database
mongoose.connect("mongodb+srv://isaachamm:iSaac-0402@cluster0.u78fx.mongodb.net/myFirstDatabase", {
  useNewUrlParser: true
});

// Configure multer so that it will upload to '../front-end/public/images'
const multer = require('multer')
const upload = multer({
  //Had to change this for Digital Ocean
  dest: '../front-end/public/images/',
  limits: {
    fileSize: 10000000
  }
});

// Create a scheme for posts in the museum: a title and a path to an image.
const postSchema = new mongoose.Schema({
  name: String,
  title: String,
  path: String,
  post: String,
  date: String,
});

// Create a model for posts in the museum.
const Post = mongoose.model('Post', postSchema);

// Get a list of all of the posts in the museum.
app.get('/api/posts', async (req, res) => {
  // console.log("GET is happening")
  try {
    let posts = await Post.find();
    res.send(posts);
  } catch (error) {
    console.log(error);
    res.sendStatus(500);
  }
});

// Upload a photo. Uses the multer middleware for the upload and then returns
// the path where the photo is stored in the file system.
app.post('/api/photos', upload.single('photo'), async (req, res) => {
  // Just a safety check
  if (!req.file) {
    return res.sendStatus(400);
  }
  res.send({
    path: "/images/" + req.file.filename
  });
});

// Create a new post in the museum: takes a title and a path to an image.
app.post('/api/posts', async (req, res) => {
  const post = new Post({
    name: req.body.name,
    title: req.body.title,
    path: req.body.path,
    post: req.body.post,
    date: req.body.date,
  });
  try {
    await post.save();
    res.send(post);
  } catch (error) {
    console.log(error);
    res.sendStatus(500);
  }
});

app.delete('/api/posts/:id', async (req, res) => {
  try {
    await Post.deleteOne({
      _id: req.params.id
    });
    res.sendStatus(200);
  } catch (error) {
    console.log(error);
    res.sendStatus(500);
  }
});

app.put('/api/posts/:id', async (req, res) => {
    try {
      let post = await Post.findOne({ _id: req.params.id });
      post.name = req.body.name;
      post.title = req.body.title;
      post.post = req.body.post;
      post.date = req.body.date;
      post.save();
      res.sendStatus(200);
    }
    catch (error) {
      console.log(error);
      res.sendStatus(500);
    }
});

app.listen(3000, () => console.log('Server listening on port 3000!'));
