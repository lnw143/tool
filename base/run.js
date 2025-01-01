function main() {
	var input = allocate(intArrayFromString(document.getElementById('input').value), ALLOC_NORMAL);
	var result=_solve(input);
	var outputBox=document.getElementById('output');
	outputBox.textContent=UTF8ToString(result);
}