<!--
  Alexandre Maros. ODAW. 2017/2
  -->

<?php
    $link = mysqli_connect("localhost", "root", "udesc", "apm");

    if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }

    $formulario_cadastro = false;
    $cadastro_ok         = false;

    if (isset($_POST['form_cadastro'])) {
        $formulario_cadastro = true;

        $email        = $_POST['email'];
        $senha        = $_POST['senha'];
        $descricao    = $_POST['descricao'];
        $idade        = $_POST['idade'];
        $newsletter   = (int) $_POST['newsletter'];
        $temBicicleta = isset($_POST['bicicleta']);
        $temCarro     = isset($_POST['carro']);

        // Verificar se ja existe um cadastro com esse email
        $stmt = mysqli_prepare($link, "SELECT * FROM usuario WHERE email = (?)");
        mysqli_stmt_bind_param($stmt, "s", $email);
        mysqli_stmt_execute($stmt);
        mysqli_stmt_store_result($stmt);
        mysqli_stmt_close($stmt);

        if (mysqli_stmt_num_rows($stmt) == 0) {
            if ($email != "" && $senha != "") {

                $stmt = mysqli_prepare($link, "INSERT INTO usuario(email, senha, descricao, idade, receber_emails) VALUES (?, ?, ?, ?, ?)");
                mysqli_stmt_bind_param($stmt, "ssssi", $email, $senha, $descricao, $idade, $newsletter);
                mysqli_stmt_execute($stmt);
                mysqli_stmt_close($stmt);
                
                if ($temBicicleta) {
                    $veic = 'b';
                    $stmt = mysqli_prepare($link, "INSERT INTO veiculos (email_usuario, tipo_veiculo) VALUES (?, ?)");
                    mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                    mysqli_stmt_execute($stmt);
                    mysqli_stmt_close($stmt);
                }
                
                if ($temCarro) {
                    $veic = 'c';
                    $stmt = mysqli_prepare($link, "INSERT INTO veiculos (email_usuario, tipo_veiculo) VALUES (?, ?)");
                    mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                    mysqli_stmt_execute($stmt);
                    mysqli_stmt_close($stmt);
                }

                $cadastro_ok = true;

            } else {
                // preencha pelo menos senha e email...
            }

        }
    }

    $query = "SELECT * FROM usuario";
    $r_usuarios = mysqli_query($link, $query);
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

        <?php if($formulario_cadastro && $cadastro_ok == false): ?>
            <p style="color:red;">Email ja cadastrado ou email e senha não preenchidos.</p>
        <?php endif ?>

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
                    <option value="1">Sim</option>
                    <option value="0">Não</option>
                </select>

                <label for="subject">Descrição</label>
                <textarea id="subject" name="descricao" placeholder="Escreva algo.." style="height:200px"></textarea>

                <input type="submit" name="form_cadastro" value="Enviar para o servidor">
                <input type="reset" value="Resetar">

            </form>
        </div>
    </section>

    <section id="contato">
        <h1>Visualizar dados ja inseridos</h1>
        <hr>
    </section>
    
    <section id="dados">
        <table style="width:100%">
            <tr>
                <th>email</th>
                <th>senha</th>
                <th>idade</th>
                <th>recebe emails?</th>
                <th>veiculos</th>
                <th>descricao</th>
                <th>Editar</th>
                <th>Deletar</th>
            </tr>
            <?php while($r = mysqli_fetch_array($r_usuarios)): ?>
            <?php 
                $query = "SELECT * FROM veiculos WHERE email_usuario = '" . $r['email'] . "'";
                $r_veiculos = mysqli_query($link, $query);
            ?>
            <tr>
                <td><?php echo $r['email'];?></td>
                <td><?php echo $r['senha'];?></td>
                <td><?php echo $r['idade'];?></td>
                <td><?php if($r['receber_emails']) echo("Sim"); else echo("Não"); ?></td>
                <td>
                    <ul>
                    <?php while($r2 = mysqli_fetch_array($r_veiculos)): ?>
                        <?php if ($r2['tipo_veiculo'] == 'c'): ?>
                            <li>Carro</li>
                        <?php elseif ($r2['tipo_veiculo'] == 'b'): ?>
                            <li>Biciclieta</li>
                        <?php endif; ?>
                    <?php endwhile; ?>
                    </ul>
                </td>
                <td><?php echo $r['descricao'];?></td>
                <td>
                    <a style="color:blue;" href="editar.php?email=<?php echo $r['email'];?>">Editar</a>
                </td>
                <td>
                    <a style="color:blue;" href="deletar.php?email=<?php echo $r['email'];?>">Deletar</a>
                </td>
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
