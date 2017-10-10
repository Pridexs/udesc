<!--
  Alexandre Maros. ODAW. 2017/2
  -->

<?php
    $link = mysqli_connect("localhost", "root", "udesc", "apm");

    if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }

    $query = "SELECT * FROM usuario";
    $results = mysqli_query($link, $query);

    $formulario_cadastro = false;
    $cadastro_ok         = false;

    if (isset($_POST['form_cadastro'])) {
        $formulario_cadastro = true;

        $email        = $_POST['email'];
        $senha        = $_POST['senha'];
        $descricao    = $_POST['descricao'];
        $idade        = $_POST['idade'];
        $temBicicleta = isset($_POST['bicicleta']);
        $temCarro     = isset($_POST['carro']);

        if ($email != "" && $senha != "") {

        } else {
            // preencha pelo menos senha e email...
        }

    }
?>

<html>
    <head>
        <meta charset="utf-8"/>
        <title>ODAW Exercicio 11</title>
        <link rel="stylesheet" type="text/css" href="./stylesheet_css2.css">
         <script src="funcoes.js"></script>
    </head>

    <header id="menu" style="height: 5%">
        <nav>
        <center>
            <ul style="font-size:1.5em;">
                <li><a href="#">Home</a></li>
                <li><a href="#sobre">Sobre</a></div></li>
                <li><a href="#contato">Formulários</a></li>
            </ul>
        </center>
        </nav>
    </header>

    <body>

    <section id="sobre">
        <h1>Sobre esta página</h1>
        <hr>

        <p>Exercício de PHP</p>

    </section>


    <section id="contato">
        <h1>Cadastro</h1>
        <hr>

        <div class="container">
            <form name="ex11" method="POST" action="index.php">

                <label for="email">Email</label>
                <input type="text" id="num1" name="email" placeholder="Digite um email..">

                <label for="senha">Senha</label>
                <input type="password" id="num2" name="senha" placeholder="Digite uma senha..">

                <label for="idade">Idade</label>
                <input type="radio" name="idade" value="mais18" checked>Tenho 18 anos ou mais
                <input type="radio" name="idade" value="menos18">Tenho menos de 18 anos
                <br><br>

                <label for="veiculo">Veiculos</label><br>
                <input type="checkbox" name="bicicleta" value="bicicleta">Eu tenho uma bicicleta<br>
                <input type="checkbox" name="carro" value="carro">Eu tenho um carro<br>
                <br>

                <label for="newsletter">Deseja receber nossos emails?</label>
                <select name="newsletter">
                    <option value="sim">Sim</option>
                    <option value="nao">Não</option>
                </select>

                <label for="subject">Descrição</label>
                <textarea id="subject" name="descricao" placeholder="Escreva algo.." style="height:200px"></textarea>

                <input type="submit" name="form_cadastro" value="Enviar para o servidor">
                <input type="reset" value="Resetar">

            </form>
        </div>
    </section>

    <section id="contato">
        <h1>Visualziar dados ja inseridos</h1>
        <hr>

        <table style="width:100%">
            <tr>
                <th>email</th>
                <th>senha</th>
                <th>idade</th>
                <th>recebe emails?</th>
                <!--<th>veiculos</th>-->
                <th>descricao</th>
            </tr>
            <?php while($r = mysqli_fetch_row($r_usuarios)): ?>
            <tr>
                <td><?php echo $r[1];?></td>
                <td><?php echo $r[2];?></td>
                <td><?php echo $r[3];?></td>
                <td><?php echo $r[4];?></td>
                <td><?php echo $r[5];?></td>
            </tr>
            <?php endwhile; ?>
        </table>

    </section>

    <!--
    <section id="contato">
        <h1>Calcular tabela fatorial</h1>
        <hr>

        <input type="submit" onclick="calcFatorial();" value="Calcular Fatorial">

        <div id="tabela_fatorial">

        </div>
    </section>
    -->

    </body>

</html
