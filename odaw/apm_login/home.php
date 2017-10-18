<!--
  Alexandre Maros. ODAW. 2017/2
  -->

<?php
    session_start();

    $link = mysqli_connect("localhost", "root", "udesc", "apm");

    if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }

    // Se nao esta logado, sai
    if ( !isset($_SESSION['email']) && !isset($_SESSION['senha']) ) {
        session_destroy();
        unset ($_SESSION['email']);
        unset ($_SESSION['senha']);
        header('location:index.php');
        die();
    }

    $email = $_SESSION['email'];
    $senha = $_SESSION['senha'];

    // Verificar se existe combinacao de usuario e senha
    $stmt = mysqli_prepare($link, "SELECT * FROM usuario WHERE email = ? AND senha = ?");
    mysqli_stmt_bind_param($stmt, "ss", $email, $senha);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_store_result($stmt);
    $qtd_rows = mysqli_stmt_num_rows($stmt);
    mysqli_stmt_close($stmt);

    // Se usuario nao confere, redirecione
    if ($qtd_rows != 1) {
        session_destroy();
        unset ($_SESSION['email']);
        unset ($_SESSION['senha']);
        header('location:index.php');
        die();
    }

    $formulario_cadastro = false;
    $cadastro_ok         = false;

    if (isset($_POST['form_cadastro'])) {
        $formulario_cadastro = true;

        $nome_aluno   = $_POST['nome_aluno'];
        $email_aluno  = $_POST['email_aluno'];
        $cpf_aluno    = $_POST['cpf_aluno'];
        $sexo_aluno   = $_POST['sexo_aluno'];
        $estado_aluno = $_POST['estado_aluno'];

        $stmt = mysqli_prepare($link, "INSERT INTO aluno (nome, email, cpf, sexo, estado) VALUES (?, ?, ?, ?, ?)");
        mysqli_stmt_bind_param($stmt, "sssss", $nome_aluno, $email_aluno, $cpf_aluno, $sexo_aluno, $estado_aluno);
        mysqli_stmt_execute($stmt);
        mysqli_stmt_close($stmt);

        $cadastro_ok = true;
    }

    $query = "SELECT * FROM aluno";
    $r_alunos = mysqli_query($link, $query);
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
                <li><a href="logout.php">Logout</a></li>
            </ul>
        </center>
        </nav>
    </header>

    <body>

    <section id="sobre">
        <h1>Bem-vindo</h1>
        <hr>

        <p>Bem vindo(a). Você está utilizando a conta pelo e-mail: <?php echo ($_SESSION['email']); ?></p>

        <?php if($formulario_cadastro && $cadastro_ok == false): ?>
            <p style="color:red;">Erro no cadastro de aluno.</p>
        <?php endif ?>

        <div id="erros">
        </div>

    </section>


    <section id="contato">
        <h1>Cadastro de Aluno</h1>
        <hr>

        <div class="container">
            <form name="form_cad_aluno" method="POST" action="home.php" onSubmit="return validar();">

                <label for="nome_aluno">Nome do Aluno</label>
                <input type="text" id="nome1" name="nome_aluno" placeholder="Digite um nome.." required>

                <label for="email_aluno">Email</label>
                <input type="text" id="email1" name="email_aluno" placeholder="Digite um email.." required>

                <label for="cpf_aluno">CPF</label>
                <input type="text" id="cpf1" name="cpf_aluno" placeholder="Digite um cpf.." required>

                <label for="sexo_aluno">Sexo</label>
                <input type="radio" name="sexo_aluno" value="m" checked>Masculino
                <input type="radio" name="sexo_aluno" value="f">Feminino
                <br><br>

                <label for="estados_brasil">Estado</label>
                <select name="estado_aluno">
                    <option value="AC">Acre</option>
                    <option value="AL">Alagoas</option>
                    <option value="AP">Amapá</option>
                    <option value="AM">Amazonas</option>
                    <option value="BA">Bahia</option>
                    <option value="CE">Ceará</option>
                    <option value="DF">Distrito Federal</option>
                    <option value="ES">Espírito Santo</option>
                    <option value="GO">Goiás</option>
                    <option value="MA">Maranhão</option>
                    <option value="MT">Mato Grosso</option>
                    <option value="MS">Mato Grosso do Sul</option>
                    <option value="MG">Minas Gerais</option>
                    <option value="PA">Pará</option>
                    <option value="PB">Paraíba</option>
                    <option value="PR">Paraná</option>
                    <option value="PE">Pernambuco</option>
                    <option value="PI">Piauí</option>
                    <option value="RJ">Rio de Janeiro</option>
                    <option value="RN">Rio Grande do Norte</option>
                    <option value="RS">Rio Grande do Sul</option>
                    <option value="RO">Rondônia</option>
                    <option value="RR">Roraima</option>
                    <option value="SC">Santa Catarina</option>
                    <option value="SP">São Paulo</option>
                    <option value="SE">Sergipe</option>
                    <option value="TO">Tocantins</option>
                </select>

                <input type="submit" name="form_cadastro" value="Cadastrar">
                <input type="reset" value="Resetar">

            </form>
        </div>
    </section>

    <section id="contato">
        <h1>Alunos cadastrados</h1>
        <hr>

        <table style="width:100%">
            <tr>
                <th>Nome</th>
                <th>E-mail</th>
                <th>CPF</th>
                <th>Sexo</th>
                <th>Estado</th>
            </tr>

            <?php while($r = mysqli_fetch_array($r_alunos)): ?>
            <tr>
                <td><?php echo $r['nome'];?></td>
                <td><?php echo $r['email'];?></td>
                <td><?php echo $r['cpf'];?></td>
                <td><?php if($r['sexo'] == 'm') echo("Masculino"); else echo("Feminino"); ?></td>
                <td><?php echo $r['estado'];?></td>
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
