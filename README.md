# CommerciumContinuum
Commercium gradual transition platform

## Technical Specifications
- Algorithm: Equihash
- Max Supply: 58 million CMM
- Block Time: 60 Seconds
- Block Reward: 8 CMM, 35% to Masternode 7.5% to Founders and Stake wallet.
### Dependencies

```shell
#The following packages are needed:
sudo apt-get install build-essential pkg-config libc6-dev m4 g++-multilib autoconf libtool ncurses-dev unzip git python python-zmq zlib1g-dev wget libcurl4-gnutls-dev bsdmainutils automake curl
```

#### Linux
```shell
git clone https://github.com/CommerciumBlockchain/CommerciumContinuum
cd CommerciumContinuum
./zcutil/fetch-params.sh
./zcutil/build.sh
```

#### MacOSX and Windows
Review Dockerfile

<h2 name="4d83" id="4d83" class="graf graf--h3 graf-after--p">Masternode Setup</h2>
A step by step guide howto setup your Commercium Masternode on Windows/Linux/MacOS local wallet &amp; Linux VPS as remote MN.</p>
<p name="62dc" id="62dc" class="graf graf--p graf-after--p">You also can run your masternode at your own computer, but it must be operational 24/7 and have a dedicated IP address. When you run your masternode your funds are safe and stored at your local wallet, not at the VPS (linux machine most cases).</p>
<h3 name="4d83" id="4d83" class="graf graf--h3 graf-after--p">Requirements:</h3>
<ul class="postList">
   <li name="ed2e" id="ed2e" class="graf graf--li graf-after--h3">100000 CMM + 0.001 CMM to pay transaction fees</li>
   <li name="b326" id="b326" class="graf graf--li graf-after--li">Commercium wallet on local Windows/Linux/MacOSX PC and VPS</li>
   <li name="c924" id="c924" class="graf graf--li graf-after--li">VPS with at least 1024 RAM, 1 CPU, &gt;20 GB HDD or more</li>
   <li name="81cc" id="81cc" class="graf graf--li graf-after--li">better to use latest ubuntu (18.04) for VPS. If you run 16.04 just install: apt-get install libgomp1</li>
   <li name="7211" id="7211" class="graf graf--li graf-after--li">putty (putty.org)</li>
</ul>
<h3 name="112c" id="112c" class="graf graf--h3 graf-after--li">PART 1: Local machine setup</h3>
<h3 name="abbd" id="abbd" class="graf graf--h3 graf-after--h3">Fresh wallet installation:</h3>
<ol class="postList">
   <li name="92c3" id="92c3" class="graf graf--li graf-after--h3">Install latest Commercium wallet on your machine from this link:<a href="https://github.com/CommerciumBlockchain/CommerciumContinuum/releases" data-href="https://github.com/CommerciumBlockchain/CommerciumContinuum/releases" class="markup--anchor markup--li-anchor" rel="nofollow noopener" target="_blank">https://github.com/CommerciumBlockchain/CommerciumContinuum/releases</a> Follow this video instructions for help:<a href="https://youtu.be/AQMogS3Enjs" data-href="https://youtu.be/AQMogS3Enjs" class="markup--anchor markup--li-anchor" rel="nofollow noopener" target="_blank">https://youtu.be/AQMogS3Enjs</a> — Windows <a href="https://youtu.be/xuLRBuvaSgU" data-href="https://youtu.be/xuLRBuvaSgU" class="markup--anchor markup--li-anchor" rel="nofollow noopener" target="_blank">https://youtu.be/xuLRBuvaSgU</a> — MacOS</li>
</ol>
<h3 name="f28c" id="f28c" class="graf graf--h3 graf-after--li">Upgrade old wallet</h3>
<p name="475e" id="475e" class="graf graf--p graf-after--h3">If you are already have old Commercium wallet then backup your data, export you private keys to import them later at new wallet: Backup `~/.commercium` - directory for MacOSX/Linux Windows users (use command shell <code class="markup--code markup--p-code">cmd.exe</code>). Press <code class="markup--code markup--p-code">Win+r</code>-&gt; write &quot;cmd&quot; -&gt; enter -&gt; copy&amp;paste his commands into the shell: <code class="markup--code markup--p-code">move %APPDATA%/ZcashParams %APPDATA%/ZcashParams.backup</code> <code class="markup--code markup--p-code">move %APPDATA%/Commercium %APPDATA%/Commercium.backup</code></p>
<ol class="postList">
   <li name="25f6" id="25f6" class="graf graf--li graf-after--p">We must edit our wallet configuration file <code class="markup--code markup--li-code">commercium.conf</code>.</li>
</ol>
<ul class="postList">
   <li name="c0d6" id="c0d6" class="graf graf--li graf-after--li">Linux: <code class="markup--code markup--li-code">~/.commercium</code> folder</li>
   <li name="5395" id="5395" class="graf graf--li graf-after--li">Windows: <code class="markup--code markup--li-code">%appdata%/Commercium</code> folder</li>
   <li name="732a" id="732a" class="graf graf--li graf-after--li">MAC: <code class="markup--code markup--li-code">~/Library/Application Support/Commercium</code></li>
</ul>
<p name="ad70" id="ad70" class="graf graf--p graf-after--li">Enter these commands on the Windows shell: <code class="markup--code markup--p-code">cd %appdata%/Commercium</code> <code class="markup--code markup--p-code">notepad commercium.conf</code> or open <code class="markup--code markup--p-code">commercium.conf</code> for editing with other editor. I suggest to edit it with external editor like Notepad++ or some other, because the default notepad on Windows 7 did not recognize unix wrapping at this file)</p>
<p name="902f" id="902f" class="graf graf--p graf-after--p">Append this new line to the end of the file:</p>
<p name="706d" id="706d" class="graf graf--p graf-after--p"><code class="markup--code markup--p-code">txindex=1</code></p>
<ol class="postList">
   <li name="26e8" id="26e8" class="graf graf--li graf-after--p">Exit windows wallet. Next we will do a full blockchain rescan to create transaction index.</li>
</ol>
<p name="b515" id="b515" class="graf graf--p graf-after--li">Run this command at Windows shell:<code class="markup--code markup--p-code">commerciumd.exe -reindex</code></p>
<p name="bc2f" id="bc2f" class="graf graf--p graf-after--p">Linux shell: <code class="markup--code markup--p-code">./commercium -reindex</code></p>
<p name="e1c0" id="e1c0" class="graf graf--p graf-after--p">OR ALTERNATIVE:</p>
<p name="c229" id="c229" class="graf graf--p graf-after--p">Windows:</p>
<p name="f5b0" id="f5b0" class="graf graf--p graf-after--p">del %APPDATA%\Commercium\peers.dat</p>
<p name="2517" id="2517" class="graf graf--p graf-after--p">del %APPDATA%\Commercium\budget.dat</p>
<p name="29f0" id="29f0" class="graf graf--p graf-after--p">del %APPDATA%\Commercium\mn*.dat</p>
<p name="698b" id="698b" class="graf graf--p graf-after--p">del %APPDATA%\Commercium\sporks /Q</p>
<p name="cff1" id="cff1" class="graf graf--p graf-after--p">del %APPDATA%\Commercium\chainstate /Q</p>
<p name="90fd" id="90fd" class="graf graf--p graf-after--p">del %APPDATA%\Commercium\blocks /Q</p>
<p name="4d10" id="4d10" class="graf graf--p graf-after--p">del %APPDATA%\Commercium\blocks\index /Q</p>
<p name="7a17" id="7a17" class="graf graf--p graf-after--p">del %APPDATA%\Commercium\database /Q</p>
<p name="f4a3" id="f4a3" class="graf graf--p graf-after--p">Linux:</p>
<p name="73a0" id="73a0" class="graf graf--p graf-after--p">rm -rf ~/.commercium/blocks</p>
<p name="5eab" id="5eab" class="graf graf--p graf-after--p">rm -rf ~/.commercium/database</p>
<p name="22e4" id="22e4" class="graf graf--p graf-after--p">rm -rf ~/.commercium/chainstate</p>
<p name="99ea" id="99ea" class="graf graf--p graf-after--p">rm -rf ~/.commercium/sporks</p>
<p name="40f8" id="40f8" class="graf graf--p graf-after--p">rm ~/.commercium/mn*.dat</p>
<p name="b74b" id="b74b" class="graf graf--p graf-after--p">rm ~/.commercium/budget.dat</p>
<p name="e68e" id="e68e" class="graf graf--p graf-after--p">rm ~/.commercium/peers.dat</p>
<p name="d218" id="d218" class="graf graf--p graf-after--p">MacOSX:</p>
<p name="724f" id="724f" class="graf graf--p graf-after--p">rm -rf Library/Application\ Support/Commercium/blocks</p>
<p name="ecb9" id="ecb9" class="graf graf--p graf-after--p">rm -rf Library/Application\ Support/Commercium/database</p>
<p name="7b68" id="7b68" class="graf graf--p graf-after--p">rm -rf Library/Application\ Support/Commercium/chainstate</p>
<p name="4041" id="4041" class="graf graf--p graf-after--p">rm -rf Library/Application\ Support/Commercium/sporks</p>
<p name="1993" id="1993" class="graf graf--p graf-after--p">rm Library/Application\ Support/Commercium/mn*.dat</p>
<p name="f7c6" id="f7c6" class="graf graf--p graf-after--p">rm Library/Application\ Support/Commercium/budget.dat</p>
<p name="6c67" id="6c67" class="graf graf--p graf-after--p">rm Library/Application\ Support/Commercium/peers.dat</p>
<p name="b709" id="b709" class="graf graf--p graf-after--p">Run new wallet release and wait until all block will be resynced again. At QT Windows wallet check tap “commerciumd” and wait until “Downloading blocks” will be 100% done. If you run <code class="markup--code markup--p-code">-reindex</code> then close you <code class="markup--code markup--p-code">cmd</code> shell and run QT wallet.</p>
<ol class="postList">
   <li name="76c4" id="76c4" class="graf graf--li graf-after--p">At this step we will send your CMM masternode coins to some new collateral address (you’ll receive masternode reward to this address). Create new “t-Addr”. You can do this at “Receive” tab. Now, send coins to this address from “send” tab. Transfer exactly 100000 CMM to this address. WARNING: save new private key for this new address and make <code class="markup--code markup--li-code">wallet.dat</code> backup!</li>
   <li name="5b4d" id="5b4d" class="graf graf--li graf-after--li">Then need to edit masternode config file to setup masternode: Open <code class="markup--code markup--li-code">masternode.conf</code> for editing:</li>
</ol>
<pre name="64f7" id="64f7" class="graf graf--pre graf-after--li"><code class="markup--code markup--pre-code">Format: alias IP:port masternodeprivkey(NODEKEY) collateral_output_txid(OUTPUTTXID) collateral_output_index(OUTPUTINDEX) <br># Example: mn1 127.0.0.2:51474 93HaYBVUCYjEMeeH1Y4sBGLALQZE1Yc1K64xiqgX37tGBDQL8Xg 2bcd3c84c84f87eaa86e4e56834c92927a07f9e18718810b92e0d0324456a67c 0</code></pre>
<p name="7c10" id="7c10" class="graf graf--p graf-after--pre">As you see above to setup masternode we must have the following data: ALIAS — masternode alias IP — VPS IP PORT — always the same 2019 NODEKEY — masternode private key (looks like generated numbers and charts) OUTPUTTXID — collateral output txid OUTPUTINDEX — collateral output index (is usually <code class="markup--code markup--p-code">0</code>)</p>
<ol class="postList">
   <li name="8dff" id="8dff" class="graf graf--li graf-after--p">Bellow is where all this requested information comes from:</li>
</ol>
<p name="83dd" id="83dd" class="graf graf--p graf-after--li">6.1 Generating NODEKEY masternode private key. Run this at local wallet where you store your coins:</p>
<p name="661f" id="661f" class="graf graf--p graf-after--p"><code class="markup--code markup--p-code">commercium-cli.exe masternode genkey</code></p>
<p name="989f" id="989f" class="graf graf--p graf-after--p">Output of this command is your Masternode Private Key (NODEKEY)</p>
<p name="ed90" id="ed90" class="graf graf--p graf-after--p">6.2 OUTPUTTXID and OUTPUTINDEX</p>
<p name="800c" id="800c" class="graf graf--p graf-after--p"><code class="markup--code markup--p-code">commercium-cli.exe masternode outputs</code></p>
<p name="3029" id="3029" class="graf graf--p graf-after--p">show “txhash” and “outputidx”. txhash is OUTPUTTXID / outputid is OUTPUTINDEX</p>
<p name="9f3e" id="9f3e" class="graf graf--p graf-after--p">6.3 Now you are ready to add all this information to <code class="markup--code markup--p-code">masternode.conf</code>.</p>
<p name="022b" id="022b" class="graf graf--p graf-after--p">Format: <code class="markup--code markup--p-code">ALIAS IP:2019 NODEKEY OUTPUTTXID OUTPUTINDEX</code></p>
<p name="8d51" id="8d51" class="graf graf--p graf-after--p">6.4 Save your <code class="markup--code markup--p-code">masternode.conf</code> changes.</p>
<h3 name="c8e5" id="c8e5" class="graf graf--h3 graf-after--p">PART 2 (VPS Setup)</h3>
<h3 name="28f4" id="28f4" class="graf graf--h3 graf-after--h3">Masternode setup process:</h3>
<p name="cbcb" id="cbcb" class="graf graf--p graf-after--h3">Connect with Putty to your VPS. Just enter IP address of your VPS at the Putty windows and login with your VPS username/password. Create new user <code class="markup--code markup--p-code">adduser cmmuser</code>. If you need video instruction check this video: <a href="https://youtu.be/vVVhtQ5Wd3g" data-href="https://youtu.be/vVVhtQ5Wd3g" class="markup--anchor markup--p-anchor" rel="nofollow noopener" target="_blank">https://youtu.be/vVVhtQ5Wd3g</a></p>
<p name="f00d" id="f00d" class="graf graf--p graf-after--p">(secure your vps)</p>
<ol class="postList">
   <li name="1a53" id="1a53" class="graf graf--li graf-after--p">linux shell: <code class="markup--code markup--li-code u-paddingRight0 u-marginRight0">wget <a href="https://github.com/CommerciumBlockchain/CommerciumContinuum/releases/download/v1.0.5/commercium_continuum-v1.0.5-linux.tar.gz" data-href="https://github.com/CommerciumBlockchain/CommerciumContinuum/releases/download/v1.0.5/commercium_continuum-v1.0.5-linux.tar.gz" class="markup--anchor markup--li-anchor" rel="nofollow noopener" target="_blank">https://github.com/CommerciumBlockchain/CommerciumContinuum/releases/download/v1.0.5/commercium_continuum-v1.0.5-linux.tar.gz</a></code></li>
   <li name="af26" id="af26" class="graf graf--li graf-after--li">Extract files with following commands:</li>
</ol>
<p name="22c5" id="22c5" class="graf graf--p graf-after--li"><code class="markup--code markup--p-code">tar -xzvf commercium_continuum-v1.0.5-linux.tar.gz</code> <code class="markup--code markup--p-code">cd ~</code> (to user home) <code class="markup--code markup--p-code">mkdir .commercium</code></p>
<p name="bdbd" id="bdbd" class="graf graf--p graf-after--p"><code class="markup--code markup--p-code">echo -e &quot;txindex=1\ndaemon=1\nrpcuser=PASSWORD\nrpcpassword=PASSWORD\nmasternode=1\nmasternodeprivkey=NODEKEY&quot; &gt; .commercium/commercium.conf</code></p>
<p name="adde" id="adde" class="graf graf--p graf-after--p">or create new config file at <code class="markup--code markup--p-code">.commercium</code> directory and edit:</p>
<p name="0dbd" id="0dbd" class="graf graf--p graf-after--p"><code class="markup--code markup--p-code">nano ~/.commercium/commercium.conf</code></p>
<p name="0121" id="0121" class="graf graf--p graf-after--p">add following:</p>
<pre name="8736" id="8736" class="graf graf--pre graf-after--p"><code class="markup--code markup--pre-code">txindex=1<br>daemon=1<br>rpcuser=PASSWORD<br>rpcpassword=PASSWORD<br>masternode=1<br>masternodeprivkey=NODEKEY</code></pre>
<p name="30bd" id="30bd" class="graf graf--p graf-after--pre"><code class="markup--code markup--p-code">NODEKEY</code> - is the key from previous part 6.1 <code class="markup--code markup--p-code">PASSWORD</code> - random password. Use secure password.</p>
<p name="0314" id="0314" class="graf graf--p graf-after--p">YOU MASTERNODE IS READY TO START!</p>
<p name="5498" id="5498" class="graf graf--p graf-after--p">on local wallet windows: <code class="markup--code markup--p-code">commercium-cli.exe startmasternode all missing</code> alternative command: <code class="markup--code markup--p-code">commercium-cli.exe startalias MASTERNODEALIAS</code></p>
<p name="e1d1" id="e1d1" class="graf graf--p graf-after--p graf--trailing">on vps <code class="markup--code markup--p-code">./commercium-cli masternode debug</code> must display &quot;Masternode successfully started.&quot; if not, wait 20 minutes and start the masternode again using the command above.</p>
</div></div></section></div>
