<?php
    $link = mysqli_connect("localhost", "root", "udesc", "apm");

    if (mysqli_connect_errno()) {
        printf("Connect failed: %s\n", mysqli_connect_error());
        exit();
    }

    $email = $_GET['email'];

    $stmt = mysqli_prepare($link, "DELETE FROM veiculos WHERE email_usuario = ?");
    mysqli_stmt_bind_param($stmt, "s", $email);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);

    $stmt = mysqli_prepare($link, "DELETE FROM usuario WHERE email = ?");
    mysqli_stmt_bind_param($stmt, "s", $email);
    mysqli_stmt_execute($stmt);
    mysqli_stmt_close($stmt);

    header("Location: index.php");
    die();
?>