<!--
  Alexandre Maros. ODAW. 2017/2
  -->

<?php
    $link = mysqli_connect("localhost", "root", "udesc", "apm");

    if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }

    // Variaveis controle
    $formulario_cadastro = false;
    $formulario_login    = false;
    $cadastro_ok         = false;
    $login_ok            = false;

    if (isset($_POST['form_cadastro'])) {
        $formulario_cadastro = true;

        $email = $_POST['email'];
        $senha = $_POST['senha'];

        $stmt = mysqli_prepare($link, "SELECT * FROM usuario WHERE email = ? AND senha = ?");
        mysqli_stmt_bind_param($stmt, "ss", $email, $senha);
        mysqli_stmt_execute($stmt);
        mysqli_stmt_store_result($stmt);
        $qtd_rows = mysqli_stmt_num_rows($stmt);
        mysqli_stmt_close($stmt);
    
        // Se nao existe usuario, adicione-o
        if ($qtd_rows == 0) {
            $stmt = mysqli_prepare($link, "INSERT INTO usuario (email, senha) VALUES (?, ?)");
            mysqli_stmt_bind_param($stmt, "ss", $email, $senha);
            mysqli_stmt_execute($stmt);
            mysqli_stmt_close($stmt);

            $cadastro_ok = true;
        }
    }

    if (isset($_POST['form_login'])) {
        $formulario_login = true;

        $email = $_POST['email'];
        $senha = $_POST['senha'];

        $stmt = mysqli_prepare($link, "SELECT * FROM usuario WHERE email = ? AND senha = ?");
        mysqli_stmt_bind_param($stmt, "ss", $email, $senha);
        mysqli_stmt_execute($stmt);
        mysqli_stmt_store_result($stmt);
        $qtd_rows = mysqli_stmt_num_rows($stmt);
        mysqli_stmt_close($stmt);
    
        // Se usuario confere, redirecione
        if ($qtd_rows == 1) {
            session_start();
            $_SESSION['email'] = $email;
            $_SESSION['senha'] = $senha;
            header('location:home.php');
            die();
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
                <li><a href="#contato">Formulários</a></li>
            </ul>
        </center>
        </nav>
    </header>

    <body>

    <section id="sobre">
        <h1>Login e Cadastro</h1>
        <hr>

        <?php if($formulario_cadastro && $cadastro_ok == false): ?>
            <p style="color:red;">Email ja cadastrado.</p>
        <?php endif ?>

        <?php if($formulario_cadastro && $cadastro_ok == true): ?>
            <p style="color:green;">Usuario cadastrado com sucesso.</p>
        <?php endif ?>

        <?php if($formulario_login && $login_ok == false): ?>
            <p style="color:red;">Email ou senha incorretos.</p>
        <?php endif ?>

    </section>

    <section id="contato">
        <h1>Login</h1>
        <hr>

        <div class="container">
            <form name="form_login" method="POST" action="index.php">

                <label for="email">Email</label>
                <input type="text" id="email2" name="email" placeholder="email">

                <label for="senha">Senha</label>
                <input type="password" id="senha2" name="senha" placeholder="senha..">

                <input type="submit" name="form_login" value="Login">
                <input type="reset" value="Resetar">
            </form>
        </div>
    </section>

    <section id="contato">
        <h1>Cadastro</h1>
        <hr>

        <div class="container">
            <form name="form_cadastro" method="POST" action="index.php">

                <label for="email">Email</label>
                <input type="text" id="email1" name="email" placeholder="Digite um email..">

                <label for="senha">Senha</label>
                <input type="password" id="senha1" name="senha" placeholder="Digite uma senha..">

                <input type="submit" name="form_cadastro" value="Cadastrar">
                <input type="reset" value="Resetar">
            </form>
        </div>
    </section>

    </body>

</html
