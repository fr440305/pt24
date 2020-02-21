
function Expr(a, b, c, d) {
	this.types = [
		"fxfxfxx",
		"fffxxxx",
		"ffxxfxx",
		"fxxffxx",
		""
	];
	this.currentTypeIndex = 0;

	this.fs = [];

	var operators = ["+", "-", "*", "/"];
	for (var i = 0; i < 4; i++) {
		for (var j = 0; j < 4; j++) {
			for (var k = 0; k < 4; k++) {
				this.fs.push(operators[i] + operators[j] + operators[k])
			}
		}
	}

	this.currentFIndex = 0;
	this.xarr = [a, b, c, d];
}

Expr.prototype.shiftType = function() {
	if (this.currentTypeIndex == this.types.length) {
		return false;
	}

	this.currentTypeIndex += 1;

	return true;
}

Expr.prototype.reset = function(a, b, c, d) {
	this.currentTypeIndex = 0;
	this.currentFIndex = 0;
	this.x = [a, b, c, d];
}

Expr.prototype.shiftOperators = function() {
	if (this.currentFIndex == this.fs.length) {
		return false; // not shiftable
	}

	this.currentFIndex += 1;

	return true;
}

Expr.prototype.calc = function() {
	var stack = [];
	var currentType = this.types[this.currentTypeIndex];
	var operators = this.fs[this.currentFIndex];
	var f = 3;
	var x = 4;

	for (var i = 6; i >= 0; i--) {
		switch (currentType[i]) {
		case 'x':
			stack.push(this.x[x]);
			break;
		case 'f':
			var r = stack.pop();
			var l = stack.pop();
			stack.push(({ // todo : use if-else.
				"+": l + r,
				"-": l - r,
				"*": l * r,
				"/": l / r
			})[operators[f]]);
		}
	}
}


Expr.prototype.toString = function(fmt) {
}

function calculateTree(tree) {
	// {}
}

function findExpr(a, b, c, d) {
	var e = new Expr(a, b, c, d);
	while () {
		while () {
			while () {
			}
		}
	}
}
