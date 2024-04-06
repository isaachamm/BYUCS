const mongoose = require('mongoose');
mongoose.connect('mongodb+srv://isaachamm:iSaac-0402@cluster0.u78fx.mongodb.net/myFirstDatabase?retryWrites=true&w=majority', {
  useUnifiedTopology: true,
  useNewUrlParser: true
});

const Cat = mongoose.model('Cat', {
  name: String
});

const kitty = new Cat({
  name: 'Morris'
});

async function work() {
  await kitty.save();
  console.log('meow');
  let kitties = await Cat.find();
  console.log(kitties);
}

work();