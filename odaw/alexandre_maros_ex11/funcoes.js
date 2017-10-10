function testarCPF() {
  strCPF = document.form_cpf.cpf.value
  var soma
  var resto
  soma = 0
  if (strCPF == "00000000000") {
    return alert("CPF Inválido")
  }

  for (i=1; i<=9; i++) {
    soma = soma + parseInt(strCPF.substring(i-1, i)) * (11 - i)
  }
  resto = (soma * 10) % 11

  if ((resto == 10) || (resto == 11)) {
    resto = 0
  }
  if (resto != parseInt(strCPF.substring(9, 10)) ) {
    return alert("CPF Inválido")
  }

  soma = 0;
  for (i = 1; i <= 10; i++) {
    soma = soma + parseInt(strCPF.substring(i-1, i)) * (12 - i);
  }

  resto = (soma * 10) % 11;

  if ((resto == 10) || (resto == 11)) {
    resto = 0
  }
  if (resto != parseInt(strCPF.substring(10, 11) ) ) {
    return alert("CPF Inválido")
  }
  return alert("CPF Válido")
}

function fat(num) {
  var rval=1;
  for (var i = 2; i <= num; i++)
    rval = rval * i;
  return rval;
}

function calcFatorial() {
  var _tbl =  document.createElement('table')
  _tbl.style.width  = '100%'

  var row = _tbl.insertRow(0);
  row.insertCell(0).outerHTML = "<th>Fatorial</th>";
  row.insertCell(0).outerHTML = "<th>^3</th>";
  row.insertCell(0).outerHTML = "<th>^2</th>";
  row.insertCell(0).outerHTML = "<th>N</th>";

  for (var i = 0; i <= 10; i++) {
    var tr = _tbl.insertRow()
    var fatorial = fat(i)

    var td = tr.insertCell()
    td.appendChild(document.createTextNode(i.toString()))
    td = tr.insertCell()
    td.appendChild(document.createTextNode((fatorial*fatorial).toString()))
    td = tr.insertCell()
    td.appendChild(document.createTextNode((fatorial*fatorial*fatorial).toString()))
    td = tr.insertCell()
    td.appendChild(document.createTextNode(fatorial.toString()))

  }

  document.getElementById('tabela_fatorial').appendChild(_tbl)
}

function imprimirTamanhos() {
  var texto = document.ex3_texto.texto.value
  for (var i = 1; i < 8; i++) {
    var p = document.createElement("p")
    p.style.fontSize = i + 10
    p.appendChild(document.createTextNode(texto))
    document.getElementById('textos_distintos').appendChild(p)
  }
}

function somarNum() {
  var n1 = document.ex4.num1.value
  var n2 = document.ex4.num2.value

  alert(parseInt(n1) + parseInt(n2))
}
