var express = require('express');
var router = express.Router();
var request = require('request');
var mongodb = require('mongodb');

// We need to work with "MongoClient" interface in order to connect to a mongodb server.
var MongoClient = mongodb.MongoClient;

// Connection URL. This is where your mongodb server is running.
var dbUrl = 'mongodb+srv://isaachamm:iSaac-0402@cluster0.u78fx.mongodb.net/myFirstDatabase?retryWrites=true&w=majority';

// we will use this variable later to insert and retrieve a "collection" of data
var collection

// Use connect method to connect to the Server
MongoClient.connect(dbUrl, { useUnifiedTopology: true, useNewUrlParser: true }, function(err, client) {
  if (err) {
    console.log('Unable to connect to the mongoDB server. Error:', err);
  }
  else {
    // HURRAY!! We are connected. :)
    console.log('Connection established to', dbUrl);

  var db = client.db('pokemon'); //Connect to the database
  db.createCollection('poke', function(err, result) {
    if (err) {
      collection = db.collection('poke');
      console.log(err); //optional, just so you can see the error
      return; // the database is likely filled anyway, so not worth checking to add to the collection
    }
    collection = result;
  // Only do the insert if the collection is empty
  collection.stats(function(err, stats) {
    if (err) { console.log(err) }
    if (stats.count == 0) { // If we havent inserted before, put the default in
      collection.insertMany(pokemon, function(err, result) {
        if (err) { console.log(err) }
        else {
          console.log('Inserted documents into the "poke" collection. The documents inserted with "_id" are:', result.length, result);
        }
      });
    }
  });
});

    /**
     * TODO: insert data here, once we've successfully connected
     */
  }
});


/* GET home page. */
router.get('/', function(req, res) {
  res.sendFile('index.html', { root: 'public' });
});

router.get('/pokemon', function(req, res) {
  console.log("In Pokemon");
  collection.find().toArray(function(err, result) {
    if (err) { console.log(err); }
    else if (result.length) {
      console.log("Query Worked");
      console.log(result);
      res.send(result);
    }
    else {
      console.log("No Documents found");
    }
  });
});

router.post('/pokemon', function(req, res) {
  console.log("In Pokemon Post");
  collection.insertOne(req.body, function(err, result) {
    if (err) {
      console.log(err);
    }
    else {
      console.log('Inserted document into the "pokemon" collection.');
      res.end('{"success" : "Updated Successfully", "status" : 200}');
    }
  });
});
module.exports = router;



/**
 * This array of pokemon will represent a piece of data in our 'database'
 */
var pokemon = [
  {
    name: 'Pikachu',
    avatarUrl: 'https://www.pokemoncenter.com/wcsstore/PokemonCatalogAssetStore/images/catalog/products/P4828/701-03127/P4828_701-03127_01.jpg'
  },
  {
    name: 'Charmander',
    avatarUrl: 'http://24.media.tumblr.com/tumblr_ma0tijLFPg1rfjowdo1_500.gif'

  },
  {
    name: 'Mew',
    avatarUrl: 'http://media3.giphy.com/media/J5JrPT8r1xGda/giphy.gif'
  },
  {
    name: 'Cubone',
    avatarUrl: 'https://assets.pokemon.com/assets/cms2/img/pokedex/full/104.png'
  },
  {
    name: 'Cleffa',
    avatarUrl: 'http://media1.giphy.com/media/pTh2K2xTJ1nag/giphy.gif'
  },
  {
    name: 'Gengar',
    avatarUrl: 'https://s-media-cache-ak0.pinimg.com/originals/7e/3b/67/7e3b67c53469cc4302035be70a7f2d60.gif'
  }
];

