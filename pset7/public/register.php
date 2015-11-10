<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if ($_POST["username"] == NULL || $_POST["password"] == NULL)
        {
            apologize("you forgot to input a field are you serious right now");
        }
        
        if ($_POST["confirmation"] != $_POST["password"] )
        {
            apologize("dude you didnt type your passwords the same are you kidding me right now");
        }
        
        $check = query("INSERT INTO users (username,hash,cash) VALUES (?,?,10000.00)", $_POST["username"], crypt($_POST["password"]));
        
        if ($check === false)
        {
            apologize("sorry bro you tried creating an account but your username was taken");
        }
        
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        
        $_SESSION["id"] = $id;
        redirect("index.php");
    }

?>
