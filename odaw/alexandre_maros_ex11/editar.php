<!--
  Alexandre Maros. ODAW. 2017/2
  -->

<?php
    $link = mysqli_connect("localhost", "root", "udesc", "apm");

    if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }

    $email = $_GET['email'];

    $formulario_editar = false;
    $editar_ok         = false;

    if (isset($_POST['form_editar'])) {
        $formulario_editar = true;

        $email        = $_POST['email'];
        $senha        = $_POST['senha'];
        $descricao    = $_POST['descricao'];
        $idade        = $_POST['idade'];
        $newsletter   = (int) $_POST['newsletter'];
        $temBicicleta = isset($_POST['bicicleta']);
        $temCarro     = isset($_POST['carro']);

        // Verificar se ja existe um cadastro com esse email
        $stmt = mysqli_prepare($link, "SELECT * FROM usuario WHERE email = ?");
        mysqli_stmt_bind_param($stmt, "s", $email);
        mysqli_stmt_execute($stmt);
        mysqli_stmt_store_result($stmt);
        $qtd_rows = mysqli_stmt_num_rows($stmt);
        mysqli_stmt_close($stmt);

        echo($qtd_rows);
        if ($qtd_rows == 1) {
            if ($email != "" && $senha != "") {

                $stmt = mysqli_prepare($link, "UPDATE usuario SET senha = ?, descricao = ?, idade = ?, receber_emails = ? WHERE email = ?");
                mysqli_stmt_bind_param($stmt, "sssis", $senha, $descricao, $idade, $newsletter, $email);
                mysqli_stmt_execute($stmt);
                mysqli_stmt_close($stmt);
                
                // Se marcou que tem bicicleta, precisa verificar se nao esta adicionado, e
                // caso nao esteja, tem que adicionar
                // Caso contrario, verifica se tem, e se tem, tem que tirar
                if ($temBicicleta) {
                    $veic = 'b';
                    $stmt = mysqli_prepare($link, "SELECT * FROM veiculos WHERE email_usuario = ? AND tipo_veiculo = ?");
                    mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                    mysqli_stmt_execute($stmt);
                    mysqli_stmt_store_result($stmt);
                    $qtd_rows = mysqli_stmt_num_rows($stmt);
                    mysqli_stmt_close($stmt);

                    // Se nao tem, tem que adicionar
                    if ($qtd_rows == 0) {
                        $stmt = mysqli_prepare($link, "INSERT INTO veiculos (email_usuario, tipo_veiculo) VALUES (?, ?)");
                        mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                        mysqli_stmt_execute($stmt);
                        mysqli_stmt_close($stmt);
                    }
                } else {
                    $veic = 'b';
                    $stmt = mysqli_prepare($link, "SELECT * FROM veiculos WHERE email_usuario = ? AND tipo_veiculo = ?");
                    mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                    mysqli_stmt_execute($stmt);
                    mysqli_stmt_store_result($stmt);
                    $qtd_rows = mysqli_stmt_num_rows($stmt);
                    mysqli_stmt_close($stmt);

                    // Se tem, tem que remover
                    if ($qtd_rows == 1) {
                        $stmt = mysqli_prepare($link, "DELETE FROM veiculos WHERE email_usuario = ? AND tipo_veiculo = ?");
                        mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                        mysqli_stmt_execute($stmt);
                        mysqli_stmt_close($stmt);
                    }
                }
                
                // Se marcou que tem carro, precisa verificar se nao esta adicionado, e
                // caso nao esteja, tem que adicionar
                // Caso contrario, verifica se tem, e se tem, tem que tirar
                if ($temCarro) {
                    $veic = 'c';
                    $stmt = mysqli_prepare($link, "SELECT * FROM veiculos WHERE email_usuario = ? AND tipo_veiculo = ?");
                    mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                    mysqli_stmt_execute($stmt);
                    mysqli_stmt_store_result($stmt);
                    $qtd_rows = mysqli_stmt_num_rows($stmt);
                    mysqli_stmt_close($stmt);

                    // Se nao tem, tem que adicionar
                    if ($qtd_rows == 0) {
                        $stmt = mysqli_prepare($link, "INSERT INTO veiculos (email_usuario, tipo_veiculo) VALUES (?, ?)");
                        mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                        mysqli_stmt_execute($stmt);
                        mysqli_stmt_close($stmt);
                    }
                } else {
                    $veic = 'c';
                    $stmt = mysqli_prepare($link, "SELECT * FROM veiculos WHERE email_usuario = ? AND tipo_veiculo = ?");
                    mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                    mysqli_stmt_execute($stmt);
                    mysqli_stmt_store_result($stmt);
                    $qtd_rows = mysqli_stmt_num_rows($stmt);
                    mysqli_stmt_close($stmt);

                    // Se tem, tem que remover
                    if ($qtd_rows == 1) {
                        $stmt = mysqli_prepare($link, "DELETE FROM veiculos WHERE email_usuario = ? AND tipo_veiculo = ?");
                        mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
                        mysqli_stmt_execute($stmt);
                        mysqli_stmt_close($stmt);
                    }
                }

                $editar_ok = true;
                header("Location: index.php");
                die();

            } else {
                // preencha pelo menos senha e email...
            }

        }
    }

    if ($email != "") {
        $stmt = mysqli_prepare($link, "SELECT * FROM usuario WHERE email = (?)");
        mysqli_stmt_bind_param($stmt, "s", $email);
        mysqli_stmt_execute($stmt);
        $result =  mysqli_stmt_get_result($stmt);
        $row = mysqli_fetch_assoc($result);
        mysqli_stmt_close($stmt);
        
        $senha = $row['senha'];
        $descricao = $row['descricao'];
        $idade = $row['idade'];
        $receber_emails = (int) $row['receber_emails'];

        $veic = 'b';
        $stmt = mysqli_prepare($link, "SELECT * FROM veiculos WHERE email_usuario = ? AND tipo_veiculo = ?");
        mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
        mysqli_stmt_execute($stmt);
        mysqli_stmt_store_result($stmt);
        $temBicicleta = mysqli_stmt_num_rows($stmt) == 1;
        mysqli_stmt_close($stmt);

        $veic = 'c';
        $stmt = mysqli_prepare($link, "SELECT * FROM veiculos WHERE email_usuario = ? AND tipo_veiculo = ?");
        mysqli_stmt_bind_param($stmt, "ss", $email, $veic);
        mysqli_stmt_execute($stmt);
        mysqli_stmt_store_result($stmt);
        $temCarro = mysqli_stmt_num_rows($stmt) == 1;
        mysqli_stmt_close($stmt);
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
                <li><a href="index.php">Home</a></li>
                <li><a href="#sobre">Sobre</a></div></li>
                <li><a href="#contato">Formulários</a></li>
            </ul>
        </center>
        </nav>
    </header>

    <body>

    <section id="contato">
        <h1>Editar</h1>
        <hr>

        <div class="container">
            <form name="ex11" method="POST" action="editar.php?email=<?php echo $email;?>">

                <label for="email">Email</label>
                <input type="text" id="num1" name="email" placeholder="Digite um email.." value="<?php echo ($email); ?>" readonly>

                <label for="senha">Senha</label>
                <input type="password" id="num2" name="senha" placeholder="Digite uma senha.." value="<?php echo($senha); ?>">

                <label for="idade">Idade</label>
                <input type="radio" name="idade" value="mais18" <?php if($idade == "mais18") echo("checked");?>>Tenho 18 anos ou mais
                <input type="radio" name="idade" value="menos18" <?php if($idade == "menos18") echo("checked");?>>Tenho menos de 18 anos
                <br><br>

                <label for="veiculo">Veiculos</label><br>
                <input type="checkbox" name="bicicleta" value="bicicleta" <?php if ($temBicicleta) echo("checked"); ?>>Eu tenho uma bicicleta<br>
                <input type="checkbox" name="carro" value="carro" <?php if ($temCarro) echo("checked"); ?>>Eu tenho um carro<br>
                <br>

                <label for="newsletter">Deseja receber nossos emails?</label>
                <select name="newsletter">
                    <option value="1" <?php if($receber_emails) echo("selected");?>>Sim</option>
                    <option value="0" <?php if(!$receber_emails) echo("selected");?>>Não</option>
                </select>

                <label for="subject">Descrição</label>
                <textarea id="subject" name="descricao" placeholder="Escreva algo.." style="height:200px"><?php echo($descricao); ?></textarea>

                <input type="submit" name="form_editar" value="Editar">

            </form>
        </div>
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
