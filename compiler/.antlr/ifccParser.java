// Generated from c:\Users\So&So\Desktop\Sophie\INSA_4IF\PLD_COMP\compilo\compiler\ifcc.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, RETURN=14, CONST=15, TEXT=16, COMMENT=17, 
		DIRECTIVE=18, WS=19;
	public static final int
		RULE_axiom = 0, RULE_prog = 1, RULE_l = 2, RULE_decl = 3, RULE_affect = 4, 
		RULE_var = 5, RULE_val = 6, RULE_expr = 7, RULE_term = 8, RULE_f = 9;
	public static final String[] ruleNames = {
		"axiom", "prog", "l", "decl", "affect", "var", "val", "expr", "term", 
		"f"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'int'", "'main'", "'('", "')'", "'{'", "'}'", "';'", "','", "'='", 
		"'+'", "'-'", "'*'", "'/'", "'return'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, null, null, null, null, 
		null, null, "RETURN", "CONST", "TEXT", "COMMENT", "DIRECTIVE", "WS"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "ifcc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ifccParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class AxiomContext extends ParserRuleContext {
		public ProgContext prog() {
			return getRuleContext(ProgContext.class,0);
		}
		public AxiomContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_axiom; }
	}

	public final AxiomContext axiom() throws RecognitionException {
		AxiomContext _localctx = new AxiomContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_axiom);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(20);
			prog();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ProgContext extends ParserRuleContext {
		public LContext l() {
			return getRuleContext(LContext.class,0);
		}
		public ProgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prog; }
	}

	public final ProgContext prog() throws RecognitionException {
		ProgContext _localctx = new ProgContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_prog);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(22);
			match(T__0);
			setState(23);
			match(T__1);
			setState(24);
			match(T__2);
			setState(25);
			match(T__3);
			setState(26);
			match(T__4);
			setState(27);
			l();
			setState(28);
			match(T__5);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LContext extends ParserRuleContext {
		public LContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_l; }
	 
		public LContext() { }
		public void copyFrom(LContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class LDeclContext extends LContext {
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public LContext l() {
			return getRuleContext(LContext.class,0);
		}
		public LDeclContext(LContext ctx) { copyFrom(ctx); }
	}
	public static class LAffectContext extends LContext {
		public AffectContext affect() {
			return getRuleContext(AffectContext.class,0);
		}
		public LContext l() {
			return getRuleContext(LContext.class,0);
		}
		public LAffectContext(LContext ctx) { copyFrom(ctx); }
	}
	public static class ReturnContext extends LContext {
		public TerminalNode RETURN() { return getToken(ifccParser.RETURN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ReturnContext(LContext ctx) { copyFrom(ctx); }
	}
	public static class LEpsilonContext extends LContext {
		public LEpsilonContext(LContext ctx) { copyFrom(ctx); }
	}

	public final LContext l() throws RecognitionException {
		LContext _localctx = new LContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_l);
		try {
			setState(44);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				_localctx = new LDeclContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(30);
				match(T__0);
				setState(31);
				decl();
				setState(32);
				match(T__6);
				setState(33);
				l();
				}
				break;
			case 2:
				_localctx = new LAffectContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(35);
				affect();
				setState(36);
				match(T__6);
				setState(37);
				l();
				}
				break;
			case 3:
				_localctx = new ReturnContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(39);
				match(RETURN);
				setState(40);
				expr();
				setState(41);
				match(T__6);
				}
				break;
			case 4:
				_localctx = new LEpsilonContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclContext extends ParserRuleContext {
		public DeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_decl; }
	 
		public DeclContext() { }
		public void copyFrom(DeclContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class DeclMultipleContext extends DeclContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public DeclMultipleContext(DeclContext ctx) { copyFrom(ctx); }
	}
	public static class DeclSimpleContext extends DeclContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public DeclSimpleContext(DeclContext ctx) { copyFrom(ctx); }
	}

	public final DeclContext decl() throws RecognitionException {
		DeclContext _localctx = new DeclContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_decl);
		try {
			setState(50);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				_localctx = new DeclMultipleContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(46);
				match(TEXT);
				setState(47);
				match(T__7);
				setState(48);
				decl();
				}
				break;
			case 2:
				_localctx = new DeclSimpleContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(49);
				match(TEXT);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AffectContext extends ParserRuleContext {
		public VarContext var() {
			return getRuleContext(VarContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public AffectContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_affect; }
	}

	public final AffectContext affect() throws RecognitionException {
		AffectContext _localctx = new AffectContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_affect);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(52);
			var();
			setState(53);
			match(T__8);
			setState(54);
			expr();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VarContext extends ParserRuleContext {
		public VarContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var; }
	 
		public VarContext() { }
		public void copyFrom(VarContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class VarTextContext extends VarContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public VarTextContext(VarContext ctx) { copyFrom(ctx); }
	}
	public static class VarDeclContext extends VarContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public VarDeclContext(VarContext ctx) { copyFrom(ctx); }
	}

	public final VarContext var() throws RecognitionException {
		VarContext _localctx = new VarContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_var);
		try {
			setState(59);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__0:
				_localctx = new VarDeclContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(56);
				match(T__0);
				setState(57);
				match(TEXT);
				}
				break;
			case TEXT:
				_localctx = new VarTextContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(58);
				match(TEXT);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ValContext extends ParserRuleContext {
		public ValContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_val; }
	 
		public ValContext() { }
		public void copyFrom(ValContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ValTextContext extends ValContext {
		public TerminalNode TEXT() { return getToken(ifccParser.TEXT, 0); }
		public ValTextContext(ValContext ctx) { copyFrom(ctx); }
	}
	public static class ValConstContext extends ValContext {
		public TerminalNode CONST() { return getToken(ifccParser.CONST, 0); }
		public ValConstContext(ValContext ctx) { copyFrom(ctx); }
	}

	public final ValContext val() throws RecognitionException {
		ValContext _localctx = new ValContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_val);
		try {
			setState(63);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case CONST:
				_localctx = new ValConstContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(61);
				match(CONST);
				}
				break;
			case TEXT:
				_localctx = new ValTextContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(62);
				match(TEXT);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class AddContext extends ExprContext {
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public AddContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class SubContext extends ExprContext {
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public SubContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Expr_singleContext extends ExprContext {
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public Expr_singleContext(ExprContext ctx) { copyFrom(ctx); }
	}

	public final ExprContext expr() throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_expr);
		try {
			setState(74);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				_localctx = new AddContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(65);
				term();
				setState(66);
				match(T__9);
				setState(67);
				expr();
				}
				break;
			case 2:
				_localctx = new SubContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(69);
				term();
				setState(70);
				match(T__10);
				setState(71);
				expr();
				}
				break;
			case 3:
				_localctx = new Expr_singleContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(73);
				term();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TermContext extends ParserRuleContext {
		public TermContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_term; }
	 
		public TermContext() { }
		public void copyFrom(TermContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class DivContext extends TermContext {
		public FContext f() {
			return getRuleContext(FContext.class,0);
		}
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public DivContext(TermContext ctx) { copyFrom(ctx); }
	}
	public static class F_singleContext extends TermContext {
		public FContext f() {
			return getRuleContext(FContext.class,0);
		}
		public F_singleContext(TermContext ctx) { copyFrom(ctx); }
	}
	public static class MultContext extends TermContext {
		public FContext f() {
			return getRuleContext(FContext.class,0);
		}
		public TermContext term() {
			return getRuleContext(TermContext.class,0);
		}
		public MultContext(TermContext ctx) { copyFrom(ctx); }
	}

	public final TermContext term() throws RecognitionException {
		TermContext _localctx = new TermContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_term);
		try {
			setState(85);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
			case 1:
				_localctx = new MultContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(76);
				f();
				setState(77);
				match(T__11);
				setState(78);
				term();
				}
				break;
			case 2:
				_localctx = new DivContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(80);
				f();
				setState(81);
				match(T__12);
				setState(82);
				term();
				}
				break;
			case 3:
				_localctx = new F_singleContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(84);
				f();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FContext extends ParserRuleContext {
		public FContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_f; }
	 
		public FContext() { }
		public void copyFrom(FContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ParContext extends FContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ParContext(FContext ctx) { copyFrom(ctx); }
	}
	public static class ConstContext extends FContext {
		public ValContext val() {
			return getRuleContext(ValContext.class,0);
		}
		public ConstContext(FContext ctx) { copyFrom(ctx); }
	}

	public final FContext f() throws RecognitionException {
		FContext _localctx = new FContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_f);
		try {
			setState(92);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case CONST:
			case TEXT:
				_localctx = new ConstContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(87);
				val();
				}
				break;
			case T__2:
				_localctx = new ParContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(88);
				match(T__2);
				setState(89);
				expr();
				setState(90);
				match(T__3);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\25a\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t\13\3"+
		"\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4"+
		"\3\4\3\4\3\4\3\4\3\4\3\4\5\4/\n\4\3\5\3\5\3\5\3\5\5\5\65\n\5\3\6\3\6\3"+
		"\6\3\6\3\7\3\7\3\7\5\7>\n\7\3\b\3\b\5\bB\n\b\3\t\3\t\3\t\3\t\3\t\3\t\3"+
		"\t\3\t\3\t\5\tM\n\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\5\nX\n\n\3\13"+
		"\3\13\3\13\3\13\3\13\5\13_\n\13\3\13\2\2\f\2\4\6\b\n\f\16\20\22\24\2\2"+
		"\2a\2\26\3\2\2\2\4\30\3\2\2\2\6.\3\2\2\2\b\64\3\2\2\2\n\66\3\2\2\2\f="+
		"\3\2\2\2\16A\3\2\2\2\20L\3\2\2\2\22W\3\2\2\2\24^\3\2\2\2\26\27\5\4\3\2"+
		"\27\3\3\2\2\2\30\31\7\3\2\2\31\32\7\4\2\2\32\33\7\5\2\2\33\34\7\6\2\2"+
		"\34\35\7\7\2\2\35\36\5\6\4\2\36\37\7\b\2\2\37\5\3\2\2\2 !\7\3\2\2!\"\5"+
		"\b\5\2\"#\7\t\2\2#$\5\6\4\2$/\3\2\2\2%&\5\n\6\2&\'\7\t\2\2\'(\5\6\4\2"+
		"(/\3\2\2\2)*\7\20\2\2*+\5\20\t\2+,\7\t\2\2,/\3\2\2\2-/\3\2\2\2. \3\2\2"+
		"\2.%\3\2\2\2.)\3\2\2\2.-\3\2\2\2/\7\3\2\2\2\60\61\7\22\2\2\61\62\7\n\2"+
		"\2\62\65\5\b\5\2\63\65\7\22\2\2\64\60\3\2\2\2\64\63\3\2\2\2\65\t\3\2\2"+
		"\2\66\67\5\f\7\2\678\7\13\2\289\5\20\t\29\13\3\2\2\2:;\7\3\2\2;>\7\22"+
		"\2\2<>\7\22\2\2=:\3\2\2\2=<\3\2\2\2>\r\3\2\2\2?B\7\21\2\2@B\7\22\2\2A"+
		"?\3\2\2\2A@\3\2\2\2B\17\3\2\2\2CD\5\22\n\2DE\7\f\2\2EF\5\20\t\2FM\3\2"+
		"\2\2GH\5\22\n\2HI\7\r\2\2IJ\5\20\t\2JM\3\2\2\2KM\5\22\n\2LC\3\2\2\2LG"+
		"\3\2\2\2LK\3\2\2\2M\21\3\2\2\2NO\5\24\13\2OP\7\16\2\2PQ\5\22\n\2QX\3\2"+
		"\2\2RS\5\24\13\2ST\7\17\2\2TU\5\22\n\2UX\3\2\2\2VX\5\24\13\2WN\3\2\2\2"+
		"WR\3\2\2\2WV\3\2\2\2X\23\3\2\2\2Y_\5\16\b\2Z[\7\5\2\2[\\\5\20\t\2\\]\7"+
		"\6\2\2]_\3\2\2\2^Y\3\2\2\2^Z\3\2\2\2_\25\3\2\2\2\t.\64=ALW^";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}