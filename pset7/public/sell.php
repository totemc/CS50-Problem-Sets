<?php

    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Validate the name
        if (empty($_POST["code"]))
        {
            apologize("you didnt even enter a stock symbol");
        }
        
        // lookup
        $stock = lookup($_POST["code"]);
        
        // Check if exists
        if ($stock === false)
        {
            apologize("invalid stock really man");
        }
        else
        {
            // Query the amount of user shares
            $rows = query("SELECT shares FROM portfolio WHERE id = ? and symbol = ?", $_SESSION["id"], strtoupper($_POST["code"]));
            if (count($rows) == 1)
            {
                $shares = $rows[0]["shares"];
            }
            else
            {
                apologize("Shares for specified symbol not found.");
            }
        
            $value = $stock["price"] * $shares;
            
            // Delete the user stocks
            $query = query("DELETE FROM portfolio where id = ? and symbol = ?", $_SESSION["id"], strtoupper($_POST["code"]));
            if ($query === false)
            {
                apologize("something happened. oops.");
            }
            
            // Update users cash
            $query = query("UPDATE users SET cash = cash + ? where id = ?", $value, $_SESSION["id"]);
            if ($query === false)
            {
               apologize("Error while selling shares.");
            }
               
            $_SESSION["cash"] += $value;
           
            $query = query("INSERT INTO history(user_id, type, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?, Now())"
            ,$_SESSION["id"], 0, strtoupper($_POST["code"]), $shares, $stock["price"]);
                
            // Redirect to home
            redirect("/");
        }
    }
    else
    {
        // Fill the array of user shares
        $rows = query("SELECT symbol FROM portfolio WHERE id = ?", $_SESSION["id"]);
        render("sell_form.php", ["title" => "Sell", "symbols" => $rows]);
    }
?>
