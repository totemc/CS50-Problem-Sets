<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["code"]))
        {
            apologize("you didn't even put in a stock symbol man c'mon what are you doing");
        }
        
        $stock = lookup($_POST["code"]);
        
        if ($stock === FALSE)
        {
            apologize("dude is that even a corrct stock symbol what are you doing");
        }
        else
        {
            render("quote_lookup.php", ["title" => "Quote", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
        }
    }
    else
    {
        render("quote_form.php", ["title" => "Lookup"]);
    }

?>
