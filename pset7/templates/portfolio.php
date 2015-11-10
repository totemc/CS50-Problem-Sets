
<table class="table table-striped">

    <thead>
        <tr>
            <th><a href="../sell.php">Sell</a></th>
            <th><a href="../buy.php">Buy</a></th>
            <th><a href="../history.php">History</a></th>
            <th><a href="../logout.php">Log out</a></th>
            <th><a href="../logout.php">Reset password</a></th>
        </tr>
    </thead>
<table class="table table-striped">

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody>
    <?php foreach($positions as $position): ?>
            <tr>
                <td><?= $position["symbol"] ?></td>
                <td><?= $position["name"] ?></td>
                <td><?= $position["shares"] ?></td>
                <td><?= number_format($position["price"], 2) ?></td>
                <td><?= number_format($position["total"], 2) ?></td>
            </tr>
    <?php endforeach ?>
    </tbody>
    </table>
    <table class="table table-striped">
    <thead>
    <tr>
    <th style="text-align:center">Cash</th>
    </tr>
    </thead>
    <tbody>
    <?php foreach($cash as $cashs): ?>
        <tr>
            <td><?= $cashs["cash"] ?></td>
        </tr>
    <?php endforeach ?>
    </tbody>
</table>

