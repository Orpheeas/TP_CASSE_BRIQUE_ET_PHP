<?php

	class Client{

	//Données membres
	private static $_ID;
	private $_Nom;
	private $_Prenom;
	private $_Adresse;
	private $_CP;
	private $_Ville;
	private $_TabFacture=array();


	// Un tableau de données doit être passé à la fonction (d'où le préfixe « array »).
	public function hydrate(array $donnees)
	{
		 foreach ($donnees as $key => $value)
			{
			  $method = 'set'.ucfirst($key);
			
				if (method_exists($this, $method))
				{
					$this->$method($value);
				}
			}
	}

	private static function initClient(){

		self::$_ID++;
	}

	public function __construct($mNom,$mPrenom,$mAdr,$mCp,$mVille){
		echo "Contructeur<br/>";
		self::initClient();
		$this->_Nom=$mNom;
		$this->_Prenom=$mPrenom;
		$this->_Adresse=$mAdr;
		$this->_CP=$mCp;
		$this->_Ville=$mVille;
	}

	public function __destruct() {
		echo '<br/>';
		echo 'Destruction de ' . self::$_ID.'<br/>';
        echo 'Destruction de ' . $this->_Nom.'<br/>';
        echo 'Destruction de '  . $this->_Prenom.'<br/>';
        echo 'Destruction de ' . $this->_Adresse.'<br/>';
        echo 'Destruction de ' . $this->_CP.'<br/>';
        echo 'Destruction de ' . $this->_Ville.'<br/>';
    }

	public function afficheClient(){

		self::initClient();
		echo $this->_Nom.'<br/>';
		echo $this->_Prenom.'<br/>';
		echo $this->_Adresse.'<br/>';
		echo $this->_CP.'<br/>';
		echo $this->_Ville.'<br/>';
		//print_r($this->_TabFacture);
		foreach (self::GetFacture() as $value){
			echo $value->afficheFacture();
		}
		echo "<br/>";
	}

	public function AjoutFacture( Facture $mFact){

		if(!in_array($mFact, $this->_TabFacture)){

			$mFact->setClient($this);
			$this->_TabFacture[]=$mFact;
		}
		//array_push($this->_TabFacture, $mFact);
		//$this->_TabFacture[]=$mFact;

	}


	//Mutateurs
	public function getID(){
		return $this->_ID;
	}

	public function getNom(){
		return $this->_Nom;
	}

	public function getPrenom(){
		return $this->_Prenom;
	}

	public function getAdresse(){
		return $this->_Adresse;
	}

	public function getCp(){
		return $this->_CP;
	}

	public function getVille(){
		return $this->_Ville;
	}


	public function setNom($mX){
		$this->_Nom=$mNom;
	}

	public function setPrenom($mX){
		$this->_Prenom=$mPrenom;
	}

	public function setAdresse($mX){
		$this->_Adresse=$mAdr;
	}

	public function setCP($mX){
		$this->_CP=$mCp;
	}

	public function setVille($mX){
		$this->_Ville=$mVille;
	}

	public function GetFacture(){

		return $this->_TabFacture;
		}

}


	class Facture{


	//Données membres
	private static $_ID;
	private $_Date;
	private $_ModeRg;
	private $_Client;
	private $_TabProduit=array();
	private $_TabDetail=array();


	public function setClient(Client $client) { 

		$this->_Client = $client;
	 }

	private static function initFacture(){

		self::$_ID++;
	}


	public function __construct($mDate,$mModeRg){
		echo "Contructeur<br/>";
		self::initFacture();
		$this->_Date=$mDate;
		$this->_ModeRg=$mModeRg;
	}

	public function __destruct() {
		echo '<br/>';
		echo 'Destruction de ' . self::$_ID.'<br/>';
        echo 'Destruction de ' . $this->_Date.'<br/>';
        echo 'Destruction de '  . $this->_ModeRg.'<br/>';
    }

	public function afficheFacture(){

		self::initFacture();
		echo $this->_Date.'<br/>';
		echo $this->_ModeRg.'<br/>';
		foreach (self::GetProduit() as $value){
			echo $value->afficheProduit();
		}
		echo "<br/>";
		echo "<br/>";
		print_r($this->_TabDetail).'<br/>';
		echo "<br/>";
	}

	public function AjoutProduit(Produit  $mProd){

		//array_push($this->_TabProduit, $mProd);
		if(!in_array($mProd, $this->_TabProduit)){
			$this->_TabProduit[]=$mProd;
		}

	}

	public function AjoutDetail( D_Facture $mDeta){

		array_push($this->_TabDetail, $mDeta);;

	}

	//Mutateurs
	public function getID(){
		return $this->_ID;
	}

	public function getDate(){
		return $this->_Date;
	}

	public function getModeRg(){
		return $this->_ModeRg;
	}


	public function setDate($mDate){
		$this->_Date=$mDate;
	}

	public function setModeRg($mModeRg){
		$this->_ModeRg=$mModeRg;
	}

	public function GetProduit(){

		return $this->_TabProduit;
		}

}


	class Produit{

	//Données membres
	private static $_ID;
	private $_Des;
	private $_PrixU;
	private $_QteProduitFacture=array();


	
	private static function initProduit(){

		self::$_ID++;
	}


	public function __construct($mDes,$mPrixU){
		echo "Contructeur<br/>";
		self::initProduit();
		$this->_Des=$mDes;
		$this->_PrixU=$mPrixU;
	}

	public function __destruct() {
		echo '<br/>';
		echo 'Destruction de ' . self::$_ID.'<br/>';
        echo 'Destruction de ' . $this->_Des.'<br/>';
        echo 'Destruction de '  . $this->_PrixU.'<br/>';
    }

	public function afficheProduit(){

		self::initProduit();
		echo $this->_Des.'<br/>';
		echo $this->_PrixU.'<br/>';
		echo "<br/>";
	}

	//Mutateurs
	public function getID(){
		return $this->_ID;
	}

	public function getDes(){
		return $this->_Des;
	}

	public function getPrixU(){
		return $this->_PrixU;
	}


	public function setDes($mDes){
		$this->_Des=$mDes;
	}

	public function setPrixU($mPrixU){
		$this->_PrixU=$mPrixU;
	}

	public function addQteProduit(D_Facture $value){

		$this->_QteProduitFacture = $value = getQte();
	}

	public function getQteProd(){
		return $this->_QteProduitFacture;
	}


}


	class D_Facture{

	//Données membre
	private $_Qte;


	public function __construct($mQte){
		echo "Contructeur<br/>";
		$this->_Qte=$mQte;
	}

	public function __destruct() {
		echo '<br/>';
		echo 'Destruction de ' . $this->_Qte.'<br/>';
    }

	public function afficheDetail(){

		echo $this->_Qte.'<br/>';
	}

	//Mutateurs
	public function getQte(){
		return $this->_Qte;
	}

	public function setQte($mQte){
		$this->_Qte=$mQte;
	}


	}

	
	class ClientManager
	{
	  private $_db; // Instance de PDO

	  public function __construct($db)
	  {
	    $this->setDb($db);
	  }

	  public function add(Client $client)
	  {
	    $q = $this->_db->prepare('INSERT INTO Client(Nom,Prenom,Adresse,CP,Ville,TabFacture) VALUES(:Nom, :Prenom, :Adresse, :CP, :Ville, :TabFacture)');

	    $q->bindValue(':Nom', $client->nom());
	    $q->bindValue(':Prenom', $client->prenom(), PDO::PARAM_STR);
	    $q->bindValue(':Adresse', $client->adresse(), PDO::PARAM_STR);
	    $q->bindValue(':CP', $client->cp(), PDO::PARAM_STR);
	    $q->bindValue(':Ville', $client->Ville(), PDO::PARAM_STR);
	    $q->bindValue(':TabFacture', $client->TabFacture(), PDO::PARAM_STR);

	    $q->execute();
	  }

	  public function delete(Client $Client)
	  {
	    $this->_db->exec('DELETE FROM Client WHERE id = '.$client->id());
	  }

	  public function get($id)
	  {
	    $id = (int) $id;

	    $q = $this->_db->query('SELECT ID, Nom, Prenom, Adresse, CP, Ville, TabFacture FROM Client WHERE id = '.$id);
	    $donnees = $q->fetch(PDO::FETCH_ASSOC);

	    return new Client($donnees);
	  }

	  public function getList()
	  {
	    $Clients = [];

	    $q = $this->_db->query('SELECT ID, Nom, Prenom, Adresse, CP, Ville, TabFacture FROM Client ORDER BY Nom');

	    while ($donnees = $q->fetch(PDO::FETCH_ASSOC))
	    {
	      $persos[] = new Client($donnees);
	    }

	    return $client;
	  }

	  public function update(Client $client)
	  {
	    $q = $this->_db->prepare('UPDATE Client SET Nom = :Nom, Prenom = :Prenom, Adresse = :Adresse, CP = :CP, Ville = :Ville, TabFacture = :TabFacture WHERE ID = :ID');

	    $q->bindValue(':Nom', $client->nom());
	    $q->bindValue(':Prenom', $client->prenom(), PDO::PARAM_STR);
	    $q->bindValue(':Adresse', $client->adresse(), PDO::PARAM_STR);
	    $q->bindValue(':CP', $client->cp(), PDO::PARAM_STR);
	    $q->bindValue(':Ville', $client->Ville(), PDO::PARAM_STR);
	    $q->bindValue(':TabFacture', $client->TabFacture(), PDO::PARAM_STR);
	    $q->bindValue(':ID', $client->ID(), PDO::PARAM_INT);


	    $q->execute();
	  }

	  public function setDb(PDO $db)
	  {
	    $this->_db = $db;
	  }
	}

	?>

<?php

	$mCli=new Client("Durand","Olivier","Milieu","68000","Strass");

	$db = new PDO('mysql:host=localhost;dbname=tests', 'root', '');

	$manager = new ClientManager($db);

	$manager->add($mCli);	

	// Faire le add puis affiche

?>