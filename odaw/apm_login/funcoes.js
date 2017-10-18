function validarCPF(cpf) {  
  //cpf = cpf.replace(/[^\d]+/g,'');    
  if(cpf == '') return false; 
  // Elimina CPFs invalidos conhecidos    
  if (cpf.length != 11 || 
      cpf == "00000000000" || 
      cpf == "11111111111" || 
      cpf == "22222222222" || 
      cpf == "33333333333" || 
      cpf == "44444444444" || 
      cpf == "55555555555" || 
      cpf == "66666666666" || 
      cpf == "77777777777" || 
      cpf == "88888888888" || 
      cpf == "99999999999")
          return false;       
  // Valida 1o digito 
  add = 0;    
  for (i=0; i < 9; i ++)       
      add += parseInt(cpf.charAt(i)) * (10 - i);  
      rev = 11 - (add % 11);  
      if (rev == 10 || rev == 11)     
          rev = 0;    
      if (rev != parseInt(cpf.charAt(9)))     
          return false;       
  // Valida 2o digito 
  add = 0;    
  for (i = 0; i < 10; i ++)        
      add += parseInt(cpf.charAt(i)) * (11 - i);  
  rev = 11 - (add % 11);  
  if (rev == 10 || rev == 11) 
      rev = 0;    
  if (rev != parseInt(cpf.charAt(10)))
      return false;       
  return true;   
}

function validarEmail(email) {
  var re = /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
  return re.test(email);
}

function validar() {
  var email = document.form_cad_aluno.email_aluno.value;
  var cpf = document.form_cad_aluno.cpf_aluno.value;
  var submeter = true;

  while (document.getElementById("err") != null) {
    document.getElementById("err").remove();
  }

  if (validarEmail(email) == false) {
    submeter = false;

    var p = document.createElement("p");
    p.id = 'err';
    p.style.color = 'red';
    p.appendChild(document.createTextNode('Erro, e-mail em formato inváldio!'));
    document.getElementById('erros').appendChild(p);
  }

  if (validarCPF(cpf) == false) {
    submeter = false;

    var p = document.createElement("p");
    p.id = 'err';
    p.style.color = 'red';
    p.appendChild(document.createTextNode('Erro, CPF inváldio!'));
    document.getElementById('erros').appendChild(p);
  }

  return submeter;
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
