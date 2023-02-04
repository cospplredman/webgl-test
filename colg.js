const screen = document.getElementById("screen");
const ctx = screen.getContext("2d", {alpha: false});
ctx.canvas.width = window.innerWidth;
ctx.canvas.height = window.innerHeight;

var mouseX = 0, mouseY = 0;

screen.addEventListener("contextmenu", (e) => {
	e.preventDefault();
});

screen.addEventListener("wheel", (e) => {
	e.preventDefault();
});

screen.addEventListener("resize", () => {
	ctx.canvas.width = window.innerWidth;
	ctx.canvas.height = window.innerHeight;
});

screen.addEventListener("pointermove", (e) => {
	mouseX = e.clientX, mouseY = e.clientY;

	let events = e.getCoalescedEvents();
	for(let i = 0; i < events.length; i++){
		//TODO
	}
});

screen.addEventListener("mouseleave", () => {
	
});

screen.addEventListener("mousedown", (e) => {
	switch(e.button){

	}
});

screen.addEventListener("mouseup", (e) => {
	switch(e.button){

	}
});

screen.addEventListener("keydown", (e) => {
	e.preventDefault();
	switch(e.code){

	}
});

screen.addEventListener("keyup", (e) => {
	switch(e.code){

	}
});

const draw = () => {
	ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height);

	ctx.fillStyle = "#00000";
	ctx.strokeStyle = "#ffffff"

	ctx.beginPath();
	ctx.arc(mouseX, mouseY, 6, 0, 2 * Math.PI);
	ctx.fill();
	ctx.stroke();
};

const loop = (fn) => {
	let q = () => {
		fn();
		requestAnimationFrame(q);
	}
	q();
};

loop(draw);
