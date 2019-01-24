<?php

if(!isset($_GET['q'])){
    die("?q=QUERY");
}

$FLAG = "flag{This_is_a_super_secret_flag}";

$q = $_GET['q'];
$q_enc = htmlspecialchars($q, ENT_QUOTES);
$js = "
<script>
(()=>{
  const esc = t => {
    return t
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/\"/g, '&quot;')
        .replace(/'/g, '&#039;');
  }
  for (let pre of document.getElementsByTagName('pre')) {
    let text = pre.innerHTML;
    let params = new URLSearchParams(window.location.search);
    let q = params.get('q');
    let idx = text.indexOf(q);
    if(idx == -1){
        pre.innerHTML = `Results for <strong>\${esc(q)}</strong> not found`;
        history.replaceState('', null, `?q=\${q}#not-found`);
        return;
    }
    history.replaceState('', null, `?q=\${q}`);
    pre.innerHTML = `\${text.substr(0, idx)}<mark>\${esc(q)}</mark>\${text.substr(idx+q.length)}`;
  }
})();
</script>
";



if(strpos($FLAG, $q) === false){
    $found = "<h1>Flag</h1><pre></pre> $js";
}
else{
    $found = "<h1>Flag</h1><pre>$FLAG </pre> $js";
}

die($found);

?>