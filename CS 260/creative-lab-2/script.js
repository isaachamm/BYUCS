

document.getElementById("artSubmit").addEventListener("click", function(event) {
	event.preventDefault();
	const value = document.getElementById("artInput").value;
	let intValue = Number(value);

if (isNaN(intValue)) {
const url ="https://collectionapi.metmuseum.org/public/collection/v1/search?q=" + value;
fetch(url)
		.then(function(response) {
			return response.json();
		}).then(function(json) {
			console.log(json);
		
	let results = "";
	results += '<h2>Results for ' + value + ' include:</h2>';
	results += '<p>';
	for (let i = 0; i < json.objectIDs.length; ++i) {
		results += json.objectIDs[i] + '<br/>'
	}
	results += '</p>';
	document.getElementById("weatherResults").innerHTML = results;
		});
	} else {
const url2 ="https://collectionapi.metmuseum.org/public/collection/v1/objects/" + value;
	fetch(url2)
		.then(function(response) {
			return response.json();
		}).then(function(json) {
			console.log(json);
		

	let results = "";
	results += '<h2>This piece is called <em>' + json.objectName + "</em>, by " + json.artistDisplayName + "</h2>";
	results += '<h4>This piece was released on ' + json.objectDate + '</h4>';
	results += '<h4>You can learn more about this piece at <a href=\'' + json.objectURL + '\'/>' + json.objectURL + '</a></h4>';
	results += '<img src=\'' + json.primaryImage + '\'/>';
	document.getElementById("weatherResults").innerHTML = results;
	
		});
};
});

// results += '<h2>' + json.main.temp + " &deg;F</h2>"
// results += "<p>"
// for (let i=0; i < json.weather.length; i++) {
// results += json.weather[i].description
// if (i !== json.weather.length - 1)
// results += ", "
// }
// results += "</p>";

// const url2="http://api.openweathermap.org/data/2.5/forecast?q=" + value + ",US&units=imperial" + "&appid=" + "3d1afcad52d07db79284de7bd6d99192";
// fetch(url2)
// 	.then(function(response) {
// 		return response.json();
// 	}).then(function(json){
// 		console.log(json);
// 		let forecastValues = "";
// 		for (let i = 0; i < json.list.length; ++i) {
// 			forecastValues += "<div class='threeHourBlock'>";
// 			forecastValues += "<h2>" + moment(json.list[i].dt_txt).format('MMMM Do YYYY, h:mm:ss a') + "</h2><br/>";
// 			forecastValues += "Temperature: " + json.list[i].main.temp + "&deg;F<br/>";
// 			forecastValues += "Feels like: " + json.list[i].main.feels_like + "&deg;F<br/>";
// 			forecastValues += "Humidity: " + json.list[i].main.humidity + "%<br/>";
// 			forecastValues += '<img src="http://openweathermap.org/img/w/' + json.list[i].weather[0].icon + '.png"/>'
// 			forecastValues += "</div>";
// 		}
// 		document.getElementById("forecastResults").innerHTML = forecastValues;
// 	})

// });
// });

// // da6d4bb0ac1386cdc69fb54336277229

